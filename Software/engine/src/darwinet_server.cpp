/*
Copyright ©2013 Jontom Xire (JontomXire@yahoo.co.uk). All
Rights Reserved. Permission to use, copy, modify, and distribute this
software and its documentation for educational, research, and
not-for-profit purposes, without fee and without a signed licensing
agreement, is hereby granted, provided that the above copyright notice,
this paragraph and the following two paragraphs appear in all copies,
modifications, and distributions.

IN NO EVENT SHALL JONTOM XIRE BE LIABLE TO ANY PARTY FOR DIRECT,
INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
EVEN IF JONTOM XIRE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

JONTOM XIRE SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING
DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS".
JONTOM XIRE HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/


#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#define __USE_GNU            /* To enable declaration of ppoll(). */
#include <poll.h>
#undef __USE_GNU
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "working_directory.hpp"
#include "config_manager.hpp"
#include "data_store.hpp"
#include "app_connection.hpp"

#include "darwinet_server.hpp"


DarwinetServer *DarwinetServer::_server = NULL;


bool DarwinetServer::Spawn(const char *home_directory)
{
    bool              result      = false;
    int               pipe_fds[2];
    pid_t             pid;
    char              msg;
    WorkingDirectory *work_dir;

    if(NULL == DarwinetServer::_server)
    {
        if(0 == pipe(pipe_fds))
        {
            pid = fork();
            if(0 < pid)
            {
                close(pipe_fds[1]);
                if((1 == read(pipe_fds[0], &msg, 1)) && ('K' == msg))
                {
                    result = true;
                }
                close(pipe_fds[0]);
            }
            else if(0 == pid)
            {
                close(pipe_fds[0]);
                msg = '\0';

                /* This code "daemonises" the process and prevents zombies. */
                (void)umask(0);
                pid = setsid();
                if(0 < pid)
                {
                    (void)freopen("/dev/null", "r", stdin);
                    (void)freopen("/dev/null", "r", stdout);
                    (void)freopen("/dev/null", "r", stderr);

                    /*
                     * If fork() fails, keep going. At worst we may get a zombie
                     * process on some platforms.
                     */
                    pid = fork();
                    if(0 < pid)
                    {
                        close(pipe_fds[1]);
                        exit(EXIT_SUCCESS);
                    }

                    work_dir = WorkingDirectory::OpenWorkingDirectory(home_directory, ".darwinet");
                    if(NULL != work_dir)
                    {
                        if(true == work_dir->LockFile("server", &pid))
                        {
                            if(0 != pid)
                            {
                                /* Already a server running. Report success and exit. */
                                delete work_dir;
                                msg = 'K';
                            }
                            else
                            {
                                /*
                                 * The server will own "work_dir" and the lock
                                 * file and free up both on deletion.
                                 */
                                DarwinetServer::_server = new DarwinetServer(work_dir);

                                if(true == DarwinetServer::_server->Bind())
                                {
                                    msg = 'K';
                                }
                                else
                                {
                                    delete DarwinetServer::_server;
                                    DarwinetServer::_server = NULL;
                                }
                            }
                        }
                    }

                    (void)write(pipe_fds[1], &msg, 1);
                    close(pipe_fds[1]);

                    if(NULL != DarwinetServer::_server)
                    {
                        DarwinetServer::_server->Run();
                        delete DarwinetServer::_server;
                        DarwinetServer::_server = NULL;
                    }

                    exit(EXIT_SUCCESS);
                }
            }
            else
            {
                close(pipe_fds[0]);
                close(pipe_fds[1]);
            }
        }
    }

    return result;
}


DarwinetServer::DarwinetServer(WorkingDirectory *dir)
{
    FILE *fp;

    _home = dir;
    _config = new ConfigManager();
    fp = _home->OpenReadFile("server.cfg");
    if(NULL != fp)
    {
        _config->Load(fp);
        (void)_home->CloseReadFile("server.cfg");
    }

    _running = false;
    _app_listen_socket = -1;
    _apps = new DataStore();
}


DarwinetServer::~DarwinetServer()
{
    FILE          *fp;
    AppConnection *app;

    app = (AppConnection *)(_apps->GetFirstData(NULL, NULL));
    while(NULL != app)
    {
        delete app;
        app = (AppConnection *)(_apps->GetNextData(NULL, NULL));
    }
    delete _apps;

    fp = _home->OpenWriteFile("server.cfg");
    if(NULL != fp)
    {
        _config->Save(fp);
        (void)_home->CloseWriteFile("server.cfg");
    }
    delete _config;

    (void)_home->RemoveFile("server");
    delete _home;
}


bool DarwinetServer::Bind()
{
    bool                result = false;
    uint16_t            port   = 0U;
    int                 reuse  = 1;
    struct sockaddr_in  addr;
    FILE               *fp;

    _app_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(0 < _app_listen_socket)
    {
        port = _config->GetUint16("app_port", 4242);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if((-1 != fcntl(_app_listen_socket, F_SETFL, O_NONBLOCK)) &&
           (0 == setsockopt(_app_listen_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))) &&
           (0 == bind(_app_listen_socket, (struct  sockaddr *)(&addr), sizeof(struct sockaddr_in))) &&
           (0 == listen(_app_listen_socket, SOMAXCONN)))
        {
            fp = _home->OpenWriteFile("server");
            if(NULL == fp)
            {
                close(_app_listen_socket);
                _app_listen_socket = -1;
            }
            else
            {
                fprintf(fp, "%u", port);
                (void)_home->CloseWriteFile("server");
                result = true;
            }
        }
        else
        {
            close(_app_listen_socket);
            _app_listen_socket = -1;
        }
    }

    return result;
}


void DarwinetServer::Run()
{
    struct sigaction  sig_act;
    sigset_t          sig_mask;
    sigset_t          orig_mask;
    struct pollfd    *fd_list;
    nfds_t            fd_count;
    uint32_t          i;
    AppConnection    *app;
    int               fds_active;

    _running = true;

    /*
     * If the signal handling setup fails we may get some strange behaviour in
     * very rare edge cases, so continue even if it fails.
     */
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGTERM);
    sig_act.sa_handler = DarwinetServer::sig_handler;
    (void)sigaction(SIGTERM, &sig_act, 0);
    (void)sigprocmask(SIG_BLOCK, &sig_mask, &orig_mask);

    while(_running)
    {
        fd_count = _apps->GetDatacount() + 1U;
        fd_list = new struct pollfd [fd_count];

        fd_list[0].fd = _app_listen_socket;
        fd_list[0].events = POLLIN;
        fd_list[0].revents = 0;

        i = 1;
        app = (AppConnection *)(_apps->GetFirstData(NULL, NULL));

        while((NULL != app) && (i < fd_count))
        {
            app->InitialisePoll(&(fd_list[i]));
            i++;
            app = (AppConnection *)(_apps->GetNextData(NULL, NULL));
        }

        fds_active = ppoll(fd_list, fd_count, NULL, &orig_mask);
        if(0 > fds_active)
        {
            if(EINTR != errno)
            {
                /* TODO: Log an error somehow. Shutdown tidily. */
                _running = false;
            }
        }
        else
        {
            /*
             * Process app connections first to ensure we get them in the
             * right order.
             */
            i = 1;
            app = (AppConnection *)(_apps->GetFirstData(NULL, NULL));

            while((NULL != app) && (i < fd_count))
            {
                app->ProcessPoll(&(fd_list[i]));
                i++;
                app = (AppConnection *)(_apps->GetNextData(NULL, NULL));
            }

            if(0 != (fd_list[0].revents & POLLERR))
            {
                /* TODO: Log an error somehow. Shutdown tidily. */
                _running = false;
            }
            else if(0 != (fd_list[0].revents & POLLERR))
            {
                /* TODO: Log an error somehow. Shutdown tidily. */
                _running = false;
            }
            else
            {
                if(0 != (fd_list[0].revents & POLLIN))
                {
                    accept_app_connection();
                }
            }
        }

        delete [] fd_list;

        if(true == _running)
        {
            process_app_connections();
        }
    }

    if(-1 != _app_listen_socket)
    {
        (void)shutdown(_app_listen_socket, SHUT_RDWR);
        (void)close(_app_listen_socket);
    }
}


void DarwinetServer::sig_handler(int sig)
{
    if(NULL != DarwinetServer::_server)
    {
        DarwinetServer::_server->Stop();
    }
}


void DarwinetServer::accept_app_connection(void)
{
    int            new_fd;
    AppConnection *app;

    if((true == _running) && (-1 < _app_listen_socket))
    {
        new_fd = accept(_app_listen_socket, NULL, NULL);
        if(0 > new_fd)
        {
            /* TODO: Handle errors better. */
            if((errno != EAGAIN) &&
               (errno != EINTR) &&
               (errno != EWOULDBLOCK))
            {
                (void)shutdown(_app_listen_socket, SHUT_RDWR);
                (void)close(_app_listen_socket);
                _app_listen_socket = -1;
                _running = false;
            }
        }
        else
        {
            app = new AppConnection(new_fd);

            /*
             * Add using the socket file descriptor value initially. Later we
             * will remove it and re-add it using a proper user/app/domain
             * combined identifier.
             */
            if(false == _apps->Add(app, (uint8_t *)(&new_fd), sizeof(int)))
            {
                /* TODO: Report/log errors. Maybe send an error message on the socket. */
                delete app;
            }
        }
    }
}


void DarwinetServer::process_app_connections(void)
{
    AppConnection *app;

    app = (AppConnection *)(_apps->GetFirstData(NULL, NULL));

    while(NULL != app)
    {


        /* TODO: Each app connection needs to process data read or errors received. At this point we need some mechanism for the app connection class to talk to this one so that this code can:
         *
         * 1) remove the app connection if an error occurred and the socket was closed.
         * 2) Send messages to other nodes if required
         *
         * We still need to decide the operational process of this class - i.e. what it needs to do. Initially we are doing a simple chat program prototype. like the non-group friends stuff I designed for Peernet. The design I want for it is an open domain - unlike Kjell-Olov's basic design, the set of domain members is potentially infinite and joining does not require invitation, nor does a full list of domain members form part of the domain information. Instead each user forms their own list of "friends" within the domain.
         */




        app = (AppConnection *)(_apps->GetNextData(NULL, NULL));
    }
}


