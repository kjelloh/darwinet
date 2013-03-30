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


#include <stdint.h>


class SocketConnection
{
public:
    SocketConnection(int socket_fd);
    virtual ~SocketConnection();

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

protected:
    int      _socket_fd;
    uint32_t  _read_buf_size;
    uint32_t  _read_byte_count;
    uint8_t  *_read_buf;
    uint32_t  _write_buf_size;
    uint32_t  _write_byte_count;
    uint8_t  *_write_buf;

};



#endif /* !_SOCKET_CONNECTION_HPP_ */

