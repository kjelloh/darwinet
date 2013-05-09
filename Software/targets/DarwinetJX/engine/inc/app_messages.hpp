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
 * This file defines the messages passed from a Darwinet application to the
 * Darwinet engine, and also in the other direction.
 */


#ifndef _APP_MESSAGES_HPP_
#define _APP_MESSAGES_HPP_


#include <stdint.h>

#include "message.hpp"


/**
 * @brief Message to request Darwinet engine version.
 *
 * 0x51564552 = QVER
 *
 * No message body.
 */

#define APP_MESSAGE_TYPE_QVER     0x51564552U

class QueryVersionMessage : public Message
{
public:
    QueryVersionMessage(uint8_t **ptr, uint32_t length) : Message(APP_MESSAGE_TYPE_QVER, 0U) { *ptr += length; }
    QueryVersionMessage() : Message(APP_MESSAGE_TYPE_QVER, 0U) {}
    virtual ~QueryVersionMessage() {}
};


/**
 * @brief Message to report Darwinet engine version.
 *
 * 0x44564552 = DVER
 *
 * Message body:
 *     Major version - 4 bytes unsigned int.
 *     Minor version - 4 bytes unsigned int.
 */

#define APP_MESSAGE_TYPE_DVER     0x44564552U

class DarwinetVersionMessage : public Message
{
public:
    DarwinetVersionMessage(uint8_t **ptr, uint32_t length);
    DarwinetVersionMessage(uint32_t major, uint32_t minor);
    virtual ~DarwinetVersionMessage() {}

    virtual uint32_t Write(uint8_t **ptr);

    void GetVersion(uint32_t *major, uint32_t *minor)
    {
        *major = _major_version;
        *minor = _minor_version;
    }

private:
    uint32_t _major_version;
    uint32_t _minor_version;

};


#endif /* !_APP_MESSAGES_HPP_ */

