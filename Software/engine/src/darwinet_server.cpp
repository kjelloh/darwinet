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
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "working_directory.hpp"
#include "config_manager.hpp"

#include "darwinet_server.hpp"


DarwinetServer *DarwinetServer::_server = NULL;


void DarwinetServer::sig_handler(int sig)
{
    if(NULL != DarwinetServer::_server)
    {
        DarwinetServer::_server->Stop();
    }
}


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
        fclose(fp);
    }

    _running = false;
    _app_listen_socket = -1;
    _max_app_connections = _config->GetUint32("max_app_connections", 8U);

}


DarwinetServer::~DarwinetServer()
{
    FILE *fp;

    fp = _home->OpenWriteFile("server.cfg");
    if(NULL != fp)
    {
        _config->Save(fp);
        fclose(fp);
    }
    delete _config;

    (void)_home->RemoveFile("server");
    delete _home;
}


bool DarwinetServer::Bind()
{
    bool                result = false;
    int                 reuse  = 1;
    struct sockaddr_in  addr;

    _app_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(0 < _app_listen_socket)
    {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(_config->GetUint16("app_port", 4242));
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

        if((-1 != fcntl(_app_listen_socket, F_SETFL, O_NONBLOCK)) &&
           (0 == setsockopt(_app_listen_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))) &&
           (0 == bind(_app_listen_socket, (struct  sockaddr *)(&addr), sizeof(struct sockaddr_in))) &&
           (0 == listen(_app_listen_socket, SOMAXCONN)))
        {
            result = true;
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

    _running = true;
    fd_list = new struct pollfd [_max_app_connections + 1U];

    /*
     * If the signal handling setup fails we may get some strange behaviour in very
     * rare edge cases, so continue even if it fails.
     */
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGTERM);
    sig_act.sa_handler = DarwinetServer::sig_handler;
    (void)sigaction(SIGTERM, &sig_act, 0);
    (void)sigprocmask(SIG_BLOCK, &sig_mask, &orig_mask);


    while(_running)
    {



sleep(1);


    }

    delete [] fd_list;

    if(-1 != _app_listen_socket)
    {
        close(_app_listen_socket);
    }
}


