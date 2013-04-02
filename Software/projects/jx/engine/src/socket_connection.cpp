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

#include "message.hpp"

#include "socket_connection.hpp"


#define INIT_BUF_SIZE   1024U
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

    _buf_grow_size = 512U;
    _max_buf_size = 8192U;
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


uint32_t SocketConnection::GetNextMessageType()
{
    uint32_t  result      = 0U;
    uint32_t  msg_hdr_len = Message::GetHeaderLength();
    uint8_t  *ptr;
    uint32_t  type;
    uint32_t  length;

    if(msg_hdr_len <= _read_byte_count)
    {
        ptr = _read_buf;
        Message::ParseHeader(&ptr, &type, &length);

        if((length + msg_hdr_len) <= _read_byte_count)
        {
            result = type;
        }
    }

    return result;
}


bool SocketConnection::IsFinished()
{
    bool result = true;

    if((0U != GetNextMessageType()) || (-1 != _socket_fd))
    {
        result = false;
    }

    return result;
}


void SocketConnection::InitialisePoll(struct pollfd *poll_fd)
{
    uint8_t *tmp_buf;

    poll_fd->fd = _socket_fd;
    poll_fd->events = 0;
    poll_fd->revents = 0;

    if((_read_buf_size < _max_buf_size) &&
       (MIN_BUF_READ > (_read_buf_size - _read_byte_count)))
    {
        _read_buf_size += _buf_grow_size;
        tmp_buf = new uint8_t [_read_buf_size];
        if(0U < _read_byte_count)
        {
            memcpy(tmp_buf, _read_buf, _read_byte_count);
        }
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


int SocketConnection::Send(Message *msg)
{
    int       result        = 0;
    uint32_t  length;
    uint32_t  req_buf_size;
    uint8_t  *tmp_buf;
    uint8_t  *ptr;

    if(0 > _socket_fd)
    {
        result = -1;
    }
    else
    {
        length = msg->GetHeaderLength() + msg->GetBodyLength();
        req_buf_size = _write_buf_size;

        while(length > (req_buf_size - _write_byte_count))
        {
            req_buf_size += _buf_grow_size;
        }

        if((req_buf_size <= _max_buf_size) && (req_buf_size > _write_buf_size))
        {
            _write_buf_size = req_buf_size;
            tmp_buf = new uint8_t [_write_buf_size];
            if(0U < _write_byte_count)
            {
                memcpy(tmp_buf, _write_buf, _write_byte_count);
            }
            delete [] _write_buf;
            _write_buf = tmp_buf;
        }

        if((_write_buf_size - _write_byte_count) < length)
        {
            result = 0;
        }
        else
        {
            ptr = &(_write_buf[_write_byte_count]);
            result = msg->Write(&ptr);
            _write_byte_count += result;
        }
    }

    delete msg;

    return result;
}


Message *SocketConnection::Recv()
{
    Message       *result      = NULL;
    ParserMap     *parsers     = GetParsers();
    uint32_t       msg_hdr_len = Message::GetHeaderLength();
    uint8_t       *ptr;
    uint32_t       type;
    uint32_t       length;
    MessageParser  parser;

    if((NULL != parsers) && (msg_hdr_len <= _read_byte_count))
    {
        ptr = _read_buf;
        Message::ParseHeader(&ptr, &type, &length);

        if((length + msg_hdr_len) <= _read_byte_count)
        {
            parser = parsers->find(type)->second;
            result = parser(&ptr, length);
        }
    }

    return result;
}


