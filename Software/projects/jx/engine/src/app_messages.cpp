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


#include <stdint.h>
#include <stdbool.h>

#include "app_messages.hpp"


DarwinetVersionMessage::DarwinetVersionMessage(uint8_t **ptr, uint32_t length)
                      : Message(APP_MESSAGE_TYPE_DVER, (sizeof(uint32_t) * 2))
{
    /* TODO: Throw an error or something if the length is wrong. */
    if(8U != length)
    {
        _major_version = 0U;
        _minor_version = 0U;
        *ptr += length;
    }
    else
    {
        _major_version = ParseUint32(ptr);
        _minor_version = ParseUint32(ptr);
    }
}


DarwinetVersionMessage::DarwinetVersionMessage(uint32_t major, uint32_t minor)
                      : Message(APP_MESSAGE_TYPE_DVER, (sizeof(uint32_t) * 2))
{
    _major_version = major;
    _minor_version = minor;
}


uint32_t DarwinetVersionMessage::Write(uint8_t **ptr)
{
    uint32_t length = Message::Write(ptr);

    length += WriteUint32(_major_version, ptr);
    length += WriteUint32(_minor_version, ptr);

    return length;
}


