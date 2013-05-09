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
 * This file defines a virtual "message" class to act as a base for a set of
 * polymorphic message classes.
 *
 * All messages consist of:
 *     A 4 byte identifier.
 *     A 4 byte message length value giving the length of the message body.
 *     A 0 to ((2^32)-1) byte message body.
 *
 * Message classes that inherit from this class have two sorts of contructors.
 * The first takes a pointer to a position in a uint8_t buffer and a length
 * value. This sort of constructor will parse the message values from the
 * buffer, updating the pointer as they go. The pointer must be updated by the
 * number of bytes specified in the length parameter. This sort of constructor
 * is used when receiving a message from a socket.
 *
 * The second sort of constructor is used to make a message to be sent. It
 * takes the values that need to be embodied in the message as its parameters.
 */


#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_


#include <stdint.h>
#include <stdbool.h>


class Message
{
public:
    Message(uint32_t type, uint32_t length) { _type = type; _length = length; }
    virtual ~Message() {}

    /**
     * @brief Write the message header to a buffer.
     *
     * All message classes inheriting from this class should implement a
     * virtual Write() function to write their message body to the buffer
     * after calling this Write() function to write the message type and length
     * to the buffer.
     *
     * @param[inout] ptr               On entry, points to the position in the
     *                                 buffer to write to.
     *                                 On exit, points to the next byte after
     *                                 the end of the header in the buffer.
     *
     * @return The number of bytes written.
     */
    virtual uint32_t Write(uint8_t **ptr);

    /**
     * @brief Get the message type.
     *
     * @return The message type value.
     */
    uint32_t GetType() { return _type; }

    /**
     * @brief Get the message header length.
     *
     * @return The length of the message header.
     */
    static uint32_t GetHeaderLength() { return (sizeof(uint32_t) * 2); };

    /**
     * @brief Get the message body length.
     *
     * @return The length of the message body.
     */
    uint32_t GetBodyLength() { return _length; };

    /**
     * @brief Parse message type and length values from a buffer.
     *
     * This function is a helper function to parse a message's type and length
     * from a buffer prior to constructing it with a parsing constructor. This
     * allows the calling code to select the correct object type and
     * constructor, and also to ensure the buffer contains enough data before
     * starting parsing the message body.
     *
     * @param[inout] ptr               On entry, points to the position in the
     *                                 buffer to read from.
     *                                 On exit, points to the next byte after
     *                                 the end of the header in the buffer.
     * @param[out]   type              The parsed message type.
     * @param[out]   length            The parsed message body length.
     */
    static void ParseHeader(uint8_t **ptr, uint32_t *type, uint32_t *length);

protected:
    /**
     * @brief Write values to a buffer.
     *
     * These functions write values of various types to a uint8_t buffer
     * without byte alignment issues using network byte order.
     *
     * It may be more efficient to move these functions into some sort of byte 
     * buffer helper class/module as they are extremely generic.
     *
     * @param[in]    value             The value to write.
     * @param[inout] ptr               On entry, points to the position in the
     *                                 buffer to write to.
     *                                 On exit, points to the next byte after
     *                                 the end of the value in the buffer.
     *
     * @return The number of bytes written.
     */
    uint32_t WriteUint32(uint32_t value, uint8_t **ptr);
    uint32_t WriteInt32(int32_t value, uint8_t **ptr);
    uint32_t WriteUint16(uint16_t value, uint8_t **ptr);
    uint32_t WriteInt16(int16_t value, uint8_t **ptr);
    uint32_t WriteBool(bool value, uint8_t **ptr);
    uint32_t WriteString(char *value, uint8_t **ptr);

    /**
     * @brief Parse values from a buffer.
     *
     * These functions parse values of various types from a uint8_t buffer
     * without byte alignment issues using network byte order.
     *
     * It may be more efficient to move these functions into some sort of byte 
     * buffer helper class/module as they are extremely generic.
     *
     * @param[inout]  ptr              On entry, points to the position in the
     *                                 buffer to read from.
     *                                 On exit, points to the next byte after
     *                                 the end of the value in the buffer.
     *
     * @return The value read from the buffer.
     */
    uint32_t ParseUint32(uint8_t **ptr);
    int32_t ParseInt32(uint8_t **ptr);
    uint16_t ParseUint16(uint8_t **ptr);
    int16_t ParseInt16(uint8_t **ptr);
    bool ParseBool(uint8_t **ptr);
    char *ParseString(uint8_t **ptr);

    uint32_t _type;
    uint32_t _length;

};


#endif /* !_MESSAGE_HPP_ */

