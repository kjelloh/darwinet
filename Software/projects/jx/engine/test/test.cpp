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


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define __USE_GNU            /* To enable declaration of ppoll(). */
#include <poll.h>
#undef __USE_GNU
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "working_directory.hpp"
#include "darwinet_server.hpp"
#include "app_connection.hpp"
#include "app_messages.hpp"


#define DEFAULT_SERVER_PORT  4242U


int read_pid(WorkingDirectory *wd, char *desc, pid_t *pid)
{
    int   fail_count = 0;
    FILE *fp;
    int   c;

    *pid = 0;

    fp = wd->OpenReadFile("server.lock");
    if(NULL == fp)
    {
        fprintf(stderr, "Failed to open %s lock file.\n", desc);
        fail_count++;
    }
    else
    {
        c = fgetc(fp);
        while(('0' <= c) && ('9' >= c))
        {
            *pid = *pid * 10;
            *pid += (c - '0');

            c = fgetc(fp);
        }

        if(0 == *pid)
        {
            fprintf(stderr, "Faportiled to read %s pid.\n", desc);
            fail_count++;
        }
        else
        {
            printf("Read pid %d for %s.\n", *pid, desc);
        }

        wd->CloseReadFile("server.lock");
    }

    return fail_count;
}


int read_port(WorkingDirectory *wd, char *desc, uint16_t *port)
{
    int   fail_count = 0;
    FILE *fp;
    int   c;

    *port = 0;

    fp = wd->OpenReadFile("server");
    if(NULL == fp)
    {
        fprintf(stderr, "Failed to open %s server file.\n", desc);
        fail_count++;
    }
    else
    {
        c = fgetc(fp);
        while(('0' <= c) && ('9' >= c))
        {
            *port = *port * 10;
            *port += (c - '0');

            c = fgetc(fp);
        }

        if(0 == *port)
        {
            fprintf(stderr, "Failed to read %s port.\n", desc);
            fail_count++;
        }
        else
        {
            printf("Read port %d for %s.\n", *port, desc);
        }

        wd->CloseReadFile("server");
    }

    return fail_count;
}


static int test_engine_connect(void)
{
    int                 fail_count = 0;
    WorkingDirectory   *wd1;
    WorkingDirectory   *wd2;
    pid_t               engine_pid = 0;
    pid_t               test_pid   = 0;
    bool                exists;
    uint16_t            port;
    struct sockaddr_in  addr;
    int                 sock_fd;
    AppConnection      *connection;
    Message            *msg        = NULL;
    struct pollfd       poll_fd;
    int                 retval;

    wd1 = WorkingDirectory::OpenWorkingDirectory("/tmp", "test");
    if(NULL == wd1)
    {
        fprintf(stderr, "Failed to create working directory for engine 1.\n");
        fail_count++;
    }
    else
    {
        if(true != DarwinetServer::Spawn("/tmp/test"))
        {
            fprintf(stderr, "Failed to spawn Darwinet engine.\n");
            fail_count++;
        }
        else
        {
            wd2 = wd1->OpenWorkingDirectory(".darwinet");
            if(NULL == wd2)
            {
                fprintf(stderr, "Failed to open Darwinet engine working directory.\n");
                fail_count++;
            }
            else
            {
                fail_count += read_pid(wd2, "Darwinet engine", &engine_pid);

                if(true != DarwinetServer::Spawn("/tmp/test"))
                {
                    fprintf(stderr, "Failed to re-spawn engine 1.\n");
                    fail_count++;
                }

                fail_count += read_pid(wd2, "re-spawned Darwinet engine", &test_pid);
                if((0 != test_pid) && (0 != engine_pid) && (test_pid != engine_pid))
                {
                    fprintf(stderr, "Re-spawning Darwinet engine created new process.\n");
                    fail_count++;
                    engine_pid = test_pid;
                }

                fail_count += read_port(wd2, "Darwinet engine", &port);
                if((0U != port) && (DEFAULT_SERVER_PORT != port))
                {
                    fprintf(stderr, "Darwinet server is using port %u, not default port %u.\n",
                            port, DEFAULT_SERVER_PORT);
                    fail_count++;
                }

                if(0U != port)
                {
                    addr.sin_family = AF_INET;
                    addr.sin_port = htons(port);
                    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

                    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
                    if(0 > sock_fd)
                    {
                        fprintf(stderr, "Failed to create socket to connect to Darwinet engine.\n");
                        fail_count++;
                    }
                    else
                    {
                        if(-1 == fcntl(sock_fd, F_SETFL, O_NONBLOCK))
                        {
                            fprintf(stderr, "failed to set socket non-blocking.\n");
                            fail_count++;
                            (void)close(sock_fd);
                        }
                        else if((0 != connect(sock_fd, (const sockaddr *)(&addr), sizeof(struct sockaddr_in))) &&
                                 (EINPROGRESS != errno))
                        {
                            fprintf(stderr, "Failed to connect to Darwinet engine (%s).\n", strerror(errno));
                            fail_count++;
                            (void)close(sock_fd);
                        }
                        else
                        {
                            connection = new AppConnection(sock_fd);
                            if((sizeof(uint32_t) * 2) != connection->Send(new QueryVersionMessage()))
                            {
                                fprintf(stderr, "Incorrect number of bytes written for Query Version message.\n");
                                fail_count++;
                            }
                            else
                            {
                                while(NULL == msg)
                                {
                                    connection->InitialisePoll(&poll_fd);
                                    retval = poll(&poll_fd, 1, 1000);
                                    if(0 > retval)
                                    {
                                        if((EAGAIN != retval) && (EINTR != retval))
                                        {
                                            fprintf(stderr, "Failed to poll socket.\n");
                                            fail_count++;
                                            break;
                                        }
                                    }
                                    else if(0 == retval)
                                    {
                                        fprintf(stderr, "Timed out waiting for response from Darwinet engine.\n");
                                        fail_count++;
                                        break;
                                    }
                                    else
                                    {
                                        connection->ProcessPoll(&poll_fd);
                                        msg = connection->Recv();

                                        if(true == connection->IsFinished())
                                        {
                                            break;
                                        }
                                    }
                                }
                            }

                            delete connection;

                            if(NULL == msg)
                            {
                                fprintf(stderr, "No reply message received from Darwinet engine.\n");
                                fail_count++;
                            }
                            else
                            {
                                /* TODO: Verify reply message is correct. */
                            }
                        }
                    }
                }

                if(0 != engine_pid)
                {
                    if(0 != kill(engine_pid, SIGTERM))
                    {
                        if(ESRCH == errno)
                        {
                            fprintf(stderr, "Failed to find engine 1 process to stop.\n");
                        }
                        else
                        {
                            fprintf(stderr, "Failed to send stop signal to engine 1 process.\n");
                        }
                        fail_count++;
                    }
                    else
                    {
                        (void)usleep(500000);
                        if(false == wd2->FileExists("server.lock", &exists))
                        {
                            fprintf(stderr, "Failed to check for engine 1 lock file.\n");
                            fail_count++;
                        }
                        else if(true == exists)
                        {
                            fprintf(stderr, "Engine 1 failed to stop cleanly.\n");
                            fail_count++;
                        }
                        else
                        {
                            /* Engine 1 stopped cleanly. */
                        }
                    }
                }

                delete wd2;
            }
        }

        delete wd1;
    }

    (void)WorkingDirectory::EraseWorkingDirectory("/tmp", "test");

    return fail_count;
}


int main(int argc, char **argv)
{
    int fail_count = 0U;

    fail_count += test_engine_connect();

    printf("%d test errors.\n", fail_count);

    return fail_count;
}


