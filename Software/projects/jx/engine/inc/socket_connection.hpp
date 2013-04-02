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

/*
 * This class implements a socket connection. It handles buffering
 * reads and writes to and from, and general operations on, a socket.
 */


#ifndef _SOCKET_CONNECTION_HPP_
#define _SOCKET_CONNECTION_HPP_


#include <map>
#include <utility>

#include <stdint.h>
#include <stdbool.h>

#include "message.hpp"


template< typename T >Message *Parser(uint8_t **ptr, uint32_t length)
{
    return new T(ptr, length);
}
typedef Message *(*MessageParser)(uint8_t **ptr, uint32_t length);
typedef std::map<uint32_t, MessageParser> ParserMap;


#define ADD_PARSER(mapname, type, classname) (mapname).insert(std::pair<uint32_t, MessageParser>((type), Parser<classname>))


class SocketConnection
{
public:
    SocketConnection(int socket_fd);
    virtual ~SocketConnection();

    /**
     * @brief Get type of next complete message on the connection.
     *
     * @return Message type if the read buffer contains a full message.
     * @retval 0 otherwise.
     */
    uint32_t GetNextMessageType();

    /**
     * @brief Check if connection is still useable.
     *
     * @retval False if connection is still connected.
     * @retval False if there are readable messages on the connection.
     * @retval True otherwise.
     */
    bool IsFinished();

    /**
     * @brief Initialise a poll() fd structure for this connection.
     *
     * @param[in]    poll_fd           poll() fd structure to initialise.
     */
    void InitialisePoll(struct pollfd *poll_fd);

    /**
     * @brief Process the results of a call to poll().
     *
     * @param[in]    poll_fd           poll() fd structure to process.
     */
    void ProcessPoll(struct pollfd *poll_fd);

    /**
     * @brief Send a message object on the connection.
     *
     * This function only writes the bytes to the output buffer. It doesn't
     * actually send the data. To do that, SocketConnection::ProcessPoll() must
     * be called.
     *
     * The message object is deleted regardless of whether or not it is successfully
     * written to the write buffer.
     *
     * @param[in]    msg               Message object to send.
     *
     * @retval -1 if the connection is no longer connected.
     * @retval 0  if the connection is unable to send the message. This
     *            typically happens when both the TCP stack send buffer and
     *            then the SocketConnection internal send buffer have filled
     *            up.
     * @return The number of bytes to be sent on success.
     */
    int Send(Message *msg);

    /*
     * @brief Get complete message if any available.
     *
     * @return Message object for next complete message read.
     * @retval NULL if no complete messages are available.
     */
    Message *Recv();

protected:
    virtual ParserMap *GetParsers() = 0;

    int        _socket_fd;
    uint32_t   _read_buf_size;
    uint32_t   _read_byte_count;
    uint8_t   *_read_buf;
    uint32_t   _write_buf_size;
    uint32_t   _write_byte_count;
    uint8_t   *_write_buf;

    uint32_t  _buf_grow_size;
    uint32_t  _max_buf_size;
};



#endif /* !_SOCKET_CONNECTION_HPP_ */

