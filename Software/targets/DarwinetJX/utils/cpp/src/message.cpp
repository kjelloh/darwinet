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
#include <string.h>

#include "message.hpp"


uint32_t Message::Write(uint8_t **ptr)
{
    uint32_t length = 0U;

    length += WriteUint32(_type, ptr);
    length += WriteUint32(_length, ptr);

    return length;
}


void Message::ParseHeader(uint8_t **ptr, uint32_t *type, uint32_t *length)
{
    *type = (((uint32_t)((*ptr)[0]) << 24) |
             ((uint32_t)((*ptr)[1]) << 16) |
             ((uint32_t)((*ptr)[2]) << 8) |
             ((uint32_t)((*ptr)[3])));
    *ptr += 4;
    *length = (((uint32_t)((*ptr)[0]) << 24) |
               ((uint32_t)((*ptr)[1]) << 16) |
               ((uint32_t)((*ptr)[2]) << 8) |
               ((uint32_t)((*ptr)[3])));
    *ptr += 4;
}


uint32_t Message::WriteUint32(uint32_t value, uint8_t **ptr)
{
    **ptr = (uint8_t)((value >> 24) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)((value >> 16) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)((value >> 8) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)(value & 0xFFU);
    (*ptr)++;

    return sizeof(uint32_t);
}


uint32_t Message::WriteInt32(int32_t value, uint8_t **ptr)
{
    uint32_t length = 0U;

    **ptr = (uint8_t)((value >> 24) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)((value >> 16) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)((value >> 8) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)(value & 0xFFU);
    (*ptr)++;

    return sizeof(int32_t);

    return length;
}


uint32_t Message::WriteUint16(uint16_t value, uint8_t **ptr)
{
    **ptr = (uint8_t)((value >> 8) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)(value & 0xFFU);
    (*ptr)++;

    return sizeof(uint16_t);
}


uint32_t Message::WriteInt16(int16_t value, uint8_t **ptr)
{
    **ptr = (uint8_t)((value >> 8) & 0xFFU);
    (*ptr)++;
    **ptr = (uint8_t)(value & 0xFFU);
    (*ptr)++;

    return sizeof(int16_t);
}


uint32_t Message::WriteBool(bool value, uint8_t **ptr)
{
    **ptr = (true == value) ? 1U : 0U;
    (*ptr)++;

    return 1U;
}


uint32_t Message::WriteString(char *value, uint8_t **ptr)
{
    uint32_t length = strlen(value);

    (void)WriteUint32(length, ptr);
    memcpy(*ptr, value, length);
    *ptr += length;

    return (sizeof(uint32_t) + length);
}


uint32_t Message::ParseUint32(uint8_t **ptr)
{
    uint32_t result = (((uint32_t)((*ptr)[0]) << 24) |
                       ((uint32_t)((*ptr)[1]) << 16) |
                       ((uint32_t)((*ptr)[2]) << 8) |
                       ((uint32_t)((*ptr)[3])));
    *ptr += 4;
    return result;
}


int32_t Message::ParseInt32(uint8_t **ptr)
{
    int32_t result = (((int32_t)((*ptr)[0]) << 24) |
                      ((int32_t)((*ptr)[1]) << 16) |
                      ((int32_t)((*ptr)[2]) << 8) |
                      ((int32_t)((*ptr)[3])));
    *ptr += 4;
    return result;
}


uint16_t Message::ParseUint16(uint8_t **ptr)
{
    uint16_t result = (((uint16_t)((*ptr)[0]) << 8) |
                       ((uint16_t)((*ptr)[1])));
    *ptr += 2;
    return result;
}


int16_t Message::ParseInt16(uint8_t **ptr)
{
    int16_t result = (((int16_t)((*ptr)[0]) << 8) |
                      ((int16_t)((*ptr)[1])));
    *ptr += 2;
    return result;
}


bool Message::ParseBool(uint8_t **ptr)
{
    uint8_t byte = (*ptr)[0];
    *ptr += 1;
    return (0U == byte) ? false : true;
}


char *Message::ParseString(uint8_t **ptr)
{
    uint16_t len = ParseUint16(ptr);
    char *result = new char [len + 1];
    memcpy(result, *ptr, len);
    *ptr += len;
    result[len] = '\0';
    return result;
}


