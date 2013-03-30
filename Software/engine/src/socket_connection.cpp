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


#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <sys/socket.h>

#include "socket_connection.hpp"


#define INIT_BUF_SIZE   1024U
#define BUF_GROW_CHUNK  512U
#define MAX_BUF_SIZE    8192U
#define MIN_BUF_READ    64U


SocketConnection::SocketConnection(int socket_fd)
{
    _socket_fd = socket_fd;
    _read_buf_size = INIT_BUF_SIZE;
    _read_byte_count = 0U;
    _read_buf = new uint8_t [_read_buf_size];
    _write_buf_size = INIT_BUF_SIZE;
    _write_byte_count = 0U;
    _write_buf = new uint8_t [_write_buf_size];
}


SocketConnection::~SocketConnection()
{
    if(-1 != _socket_fd)
    {
        (void)shutdown(_socket_fd, SHUT_RDWR);
        (void)close(_socket_fd);
    }

    delete [] _read_buf;
    delete [] _write_buf;
}


void SocketConnection::InitialisePoll(struct pollfd *poll_fd)
{
    uint8_t *tmp_buf;

    poll_fd->fd = _socket_fd;
    poll_fd->events = 0;
    poll_fd->revents = 0;

    if((_read_buf_size < MAX_BUF_SIZE) &&
       (MIN_BUF_READ > (_read_buf_size - _read_byte_count)))
    {
        _read_buf_size += BUF_GROW_CHUNK;
        tmp_buf = new uint8_t [_read_buf_size];
        memcpy(tmp_buf, _read_buf, _read_byte_count);
        delete [] _read_buf;
        _read_buf = tmp_buf;
    }

    if(0U < (_read_buf_size - _read_byte_count))
    {
        poll_fd->events |= POLLIN;
    }

    if(0U < _write_byte_count)
    {
        poll_fd->events |= POLLOUT;
    }
}


void SocketConnection::ProcessPoll(struct pollfd *poll_fd)
{
    int byte_count;

    if(poll_fd->fd == _socket_fd)
    {
        if(0 != (poll_fd->revents & POLLERR))
        {
            /* Error should probably be logged. */
            (void)shutdown(_socket_fd, SHUT_RDWR);
            (void)close(_socket_fd);
            _socket_fd = -1;
        }
        else if(0 != (poll_fd->revents & POLLHUP))
        {
            /* Client has gone away. */
            (void)shutdown(_socket_fd, SHUT_RDWR);
            (void)close(_socket_fd);
            _socket_fd = -1;
        }
        else
        {
            if((0 < _write_byte_count) && (0 != (poll_fd->revents & POLLOUT)))
            {
                byte_count = send(_socket_fd, _write_buf, _write_byte_count, 0);
                if(0 > byte_count)
                {
                    if((errno != EAGAIN) &&
                       (errno != EINTR) &&
                       (errno != EWOULDBLOCK))
                    {
                        (void)shutdown(_socket_fd, SHUT_RDWR);
                        (void)close(_socket_fd);
                        _socket_fd = -1;
                    }
                }
                else
                {
                    _write_byte_count -= byte_count;
                    if(0 < _write_byte_count)
                    {
                        (void)memmove(_write_buf, (_write_buf + byte_count), _write_byte_count);
                    }
                }
            }

            if((0 != poll_fd->revents & POLLIN) && (0 < (_read_buf_size - _read_byte_count)))
            {
                byte_count = recv(_socket_fd, (_read_buf + _read_byte_count), (_read_buf_size - _read_byte_count), 0);
                if(0 > byte_count)
                {
                    if((errno != EAGAIN) &&
                       (errno != EINTR) &&
                       (errno != EWOULDBLOCK))
                    {
                        (void)shutdown(_socket_fd, SHUT_RDWR);
                        (void)close(_socket_fd);
                        _socket_fd = -1;
                    }
                }
                else
                {
                    _read_byte_count += byte_count;
                }
            }
        }
    }
}


