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
#include <ctype.h>

#include "data_store.hpp"

#include "config_manager.hpp"


typedef enum
{
    PARSE_PRE_NAME,
    PARSE_NAME,
    PARSE_POST_NAME,
    PARSE_PRE_VALUE,
    PARSE_UINT,
    PARSE_INT,
    PARSE_BOOL,
    PARSE_STRING,
    PARSE_POST_VALUE,
    PARSE_COMMENT,
    PARSE_INVALID
} ParseStage;


typedef enum
{
    CONFIG_TYPE_INT64,    /* Signed/negative 64 bit integer. */
    CONFIG_TYPE_UINT64,   /* Unsigned 64 bit integer. */
    CONFIG_TYPE_UINT63,   /* 64 bit integer of undetermined signedness. */
    CONFIG_TYPE_INT32,    /* Signed/negative 32 bit integer. */
    CONFIG_TYPE_UINT32,   /* Unsigned 32 bit integer. */
    CONFIG_TYPE_UINT31,   /* 32 bit integer of undetermined signedness. */
    CONFIG_TYPE_INT16,    /* Signed/negative 16 bit integer. */
    CONFIG_TYPE_UINT16,   /* Unsigned 16 bit integer. */
    CONFIG_TYPE_UINT15,   /* 16 bit integer of undetermined signedness. */
    CONFIG_TYPE_INT8,     /* Signed/negative 8 bit integer. */
    CONFIG_TYPE_UINT8,    /* Unsigned 8 bit integer. */
    CONFIG_TYPE_UINT7,    /* 8 bit integer of undetermined signedness. */
    CONFIG_TYPE_BOOL,     /* Boolean. */
    CONFIG_TYPE_STRING,   /* String. */
    CONFIG_TYPE_INVALID
} ConfigType;


typedef struct
{
    ConfigType  type;
    union
    {
        uint64_t  uint64_val;
        int64_t   int64_val;
        uint32_t  uint32_val;
        int32_t   int32_val;
        uint16_t  uint16_val;
        int16_t   int16_val;
        uint8_t   uint8_val;
        int8_t    int8_val;
        bool      bool_val;
        char     *str_val;
    } value;
} ConfigValue;


static void enlarge_string(char **string, char **ptr, uint32_t *len)
{
    char *new_buffer;

    new_buffer = new char [*len + 8U];
    memcpy(new_buffer, *string, *len);
    delete [] *string;

    *ptr = new_buffer + (*ptr - *string);
    *string = new_buffer;
    *len += 8U;
}


ConfigManager::ConfigManager()
{
    _data = new DataStore();
}


ConfigManager::~ConfigManager()
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->GetFirstData(NULL, NULL));

    while(NULL != config_value)
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
        delete config_value;

        config_value = (ConfigValue *)(_data->GetNextData(NULL, NULL));
    }
    delete _data;
}


void ConfigManager::Load(FILE *fp)
{
    int          c;
    ConfigValue *config_value = NULL;
    ParseStage   stage;
    ParseStage   next_stage;
    char        *name;
    uint32_t     name_length;
    uint64_t     uint_val;
    uint32_t     strval_length;
    char         delimiter;
    char        *ptr;


    name_length = 32U;
    name = new char [name_length];

    while(EOF != (c = fgetc(fp)))
    {
        if(NULL == config_value)
        {
            config_value = new ConfigValue;
            config_value->type = CONFIG_TYPE_INVALID;
            config_value->value.str_val = NULL;
            stage = PARSE_PRE_NAME;
            next_stage = PARSE_INVALID;
            strval_length = 0U;
            delimiter = '\0';
            ptr = name;
        }

        if((PARSE_STRING == stage) && (' ' <= c))
        {
            if(strval_length == (uint32_t)(ptr - config_value->value.str_val))
            {
                enlarge_string(&(config_value->value.str_val), &ptr, &strval_length);
            }

            switch(c)
            {
                case '\\':
                {
                    c = fgetc(fp);
                    if(EOF == c)
                    {
                        delete [] config_value->value.str_val;
                        delete config_value;
                        config_value = NULL;
                        stage = PARSE_PRE_NAME;

                    }
                    else
                    {
                        *ptr = (char)c;
                        ptr++;
                    }
                    break;
                }
                case '\'':
                case '"':
                {
                    if(delimiter == c)
                    {
                        delimiter = '\0';
                        *ptr = '\0';
                        next_stage = PARSE_POST_VALUE;
                    }
                    else
                    {
                        *ptr = (char)c;
                        ptr++;
                    }
                    break;
                }
                default:
                {
                    *ptr = (char)c;
                    ptr++;
                    break;
                }
            }
        }
        else if(' ' > c)
        {
            switch(stage)
            {
                case PARSE_UINT:
                case PARSE_INT:
                case PARSE_BOOL:
                {
                    next_stage = PARSE_POST_VALUE;
                    break;
                }
                case PARSE_STRING:
                {
                    delete [] config_value->value.str_val;
                    delete config_value;
                    config_value = NULL;
                    stage = PARSE_PRE_NAME;
                    break;
                }
                default:
                {
                    delete config_value;
                    config_value = NULL;
                    stage = PARSE_PRE_NAME;
                    break;
                }
            }
        }
        else if(' ' == c)
        {
            switch(stage)
            {
                case PARSE_NAME:
                {
                    if(name_length == (uint32_t)(ptr - name))
                    {
                        enlarge_string(&name, &ptr, &name_length);
                    }

                    *ptr = '\0';
                    stage = PARSE_POST_NAME;
                    break;
                }
                case PARSE_UINT:
                case PARSE_INT:
                case PARSE_BOOL:
                {
                    next_stage = PARSE_POST_VALUE;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        else if('=' == c)
        {
            switch(stage)
            {
                case PARSE_PRE_NAME:
                {
                    /* Can't have a value without a name. */
                    stage = PARSE_COMMENT;
                    break;
                }
                case PARSE_NAME:
                {
                    if(name_length == (uint32_t)(ptr - name))
                    {
                        enlarge_string(&name, &ptr, &name_length);
                    }

                    *ptr = '\0';
                    stage = PARSE_PRE_VALUE;
                    break;
                }
                case PARSE_POST_NAME:
                {
                    stage = PARSE_PRE_VALUE;
                    break;
                }
                default:
                {
                    /* Invalid character - ignore line. */
                    stage = PARSE_COMMENT;
                    break;
                }
            }
        }
        else if('#' == c)
        {
            switch(stage)
            {
                case PARSE_UINT:
                case PARSE_INT:
                case PARSE_BOOL:
                {
                    next_stage = PARSE_COMMENT;
                    break;
                }
                default:
                {
                    stage = PARSE_COMMENT;
                    break;
                }
            }
        }
        else if((stage == PARSE_PRE_VALUE) && (('"' == c) || ('\'' == c)))
        {
            strval_length = 32U;
            config_value->value.str_val = new char [strval_length];
            ptr = config_value->value.str_val;
            delimiter = (char)c;
            stage = PARSE_STRING;
        }
        else if((stage == PARSE_PRE_VALUE) && ('-' == c))
        {
            uint_val = 0U;
            stage = PARSE_INT;
        }
        else if(('0' <= c) && ('9' >= c))
        {
            switch(stage)
            {
                case PARSE_PRE_NAME:
                case PARSE_NAME:
                {
                    if(name_length == (uint32_t)(ptr - name))
                    {
                        enlarge_string(&name, &ptr, &name_length);
                    }

                    *ptr = (char)c;
                    ptr++;
                    break;
                }
                case PARSE_PRE_VALUE:
                {
                    uint_val = c - '0';
                    stage = PARSE_UINT;
                    break;
                }
                case PARSE_UINT:
                case PARSE_INT:
                {
                    uint_val = (uint_val * 10U) + (c - '0');
                    break;
                }
                default:
                {
                    /* Invalid character - ignore line. */
                    stage = PARSE_COMMENT;
                    break;
                }
            }
        }
        else if ((('a' <= c) && ('z' >= c)) ||
                 (('A' <= c) && ('Z' >= c)) ||
                 ('_' == c))
        {
            switch(stage)
            {
                case PARSE_PRE_NAME:
                case PARSE_NAME:
                {
                    if(name_length == (uint32_t)(ptr - name))
                    {
                        enlarge_string(&name, &ptr, &name_length);
                    }

                    *ptr = (char)c;
                    ptr++;
                    stage = PARSE_NAME;
                    break;
                }
                case PARSE_PRE_VALUE:
                {
                    strval_length = 32U;
                    config_value->value.str_val = new char [strval_length];
                    ptr = config_value->value.str_val;
                    stage = PARSE_BOOL;
                    *ptr = (char)toupper(c);
                    ptr++;
                    break;
                }
                case PARSE_BOOL:
                {
                    if(strval_length == (uint32_t)(ptr - config_value->value.str_val))
                    {
                        enlarge_string(&(config_value->value.str_val), &ptr, &strval_length);
                    }
                    *ptr = (char)toupper(c);
                    ptr++;
                    break;
                }
                default:
                {
                    /* Invalid character - ignore line. */
                    stage = PARSE_COMMENT;
                    break;
                }
            }
        }
        else
        {
            /* Invalid character - ignore line. */
            stage = PARSE_COMMENT;
        }

        if(PARSE_INVALID != next_stage)
        {
            switch(stage)
            {
                case PARSE_INT:
                {
                    if(uint_val < ((uint64_t)1U << 7))
                    {
                        config_value->type = CONFIG_TYPE_INT8;
                        config_value->value.int8_val = -1 * (int8_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 15))
                    {
                        config_value->type = CONFIG_TYPE_INT16;
                        config_value->value.int16_val = -1 * (int16_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 31))
                    {
                        config_value->type = CONFIG_TYPE_INT32;
                        config_value->value.int32_val = -1 * (int32_t)uint_val;
                    }
                    else
                    {
                        config_value->type = CONFIG_TYPE_INT64;
                        config_value->value.int64_val = -1 * (int64_t)uint_val;
                    }
                    break;
                }
                case PARSE_UINT:
                {
                    if(uint_val < ((uint64_t)1U << 7))
                    {
                        config_value->type = CONFIG_TYPE_UINT7;
                        config_value->value.int8_val = (int8_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 8))
                    {
                        config_value->type = CONFIG_TYPE_UINT8;
                        config_value->value.uint8_val = (uint8_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 15))
                    {
                        config_value->type = CONFIG_TYPE_UINT15;
                        config_value->value.int16_val = (int16_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 16))
                    {
                        config_value->type = CONFIG_TYPE_UINT16;
                        config_value->value.uint16_val = (uint16_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 31))
                    {
                        config_value->type = CONFIG_TYPE_UINT31;
                        config_value->value.int32_val = (int32_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 32))
                    {
                        config_value->type = CONFIG_TYPE_UINT32;
                        config_value->value.uint32_val = (uint32_t)uint_val;
                    }
                    else if(uint_val < ((uint64_t)1U << 63))
                    {
                        config_value->type = CONFIG_TYPE_UINT63;
                        config_value->value.int64_val = (int64_t)uint_val;
                    }
                    else
                    {
                        config_value->type = CONFIG_TYPE_UINT64;
                        config_value->value.uint64_val = uint_val;
                    }
                    break;
                }
                case PARSE_BOOL:
                {
                    config_value->type = CONFIG_TYPE_BOOL;

                    if(strval_length == (uint32_t)(ptr - config_value->value.str_val))
                    {
                        enlarge_string(&(config_value->value.str_val), &ptr, &strval_length);
                    }

                    *ptr = '\0';
                    ptr = config_value->value.str_val;
                    config_value->value.str_val = NULL;

                    if((0 == strcmp(ptr, "TRUE")) ||
                       (0 == strcmp(ptr, "YES")))
                    {
                        config_value->value.bool_val = true;
                    }
                    else if((0 == strcmp(ptr, "FALSE")) ||
                            (0 == strcmp(ptr, "NO")))
                    {
                        config_value->value.bool_val = false;
                    }
                    else
                    {
                        delete config_value;
                        config_value = NULL;
                    }

                    delete [] ptr;
                    break;
                }
                case PARSE_STRING:
                {
                    config_value->type = CONFIG_TYPE_STRING;
                    break;
                }
                default:
                {
                    delete config_value;
                    config_value = NULL;
                    break;
                }
            }

            stage = next_stage;

            if(NULL != config_value)
            {
                if(true != _data->Add(config_value, name))
                {
                    delete config_value;
                }
                config_value = NULL;
            }
        }
    }
}


void ConfigManager::Save(FILE *fp)
{
    ConfigValue *config_value;
    char        *name;
    char        *ptr;

    config_value = (ConfigValue *)(_data->GetFirstData((uint8_t **)(&name), NULL));

    while(NULL != config_value)
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_INT64:
            case CONFIG_TYPE_UINT63:
            {
                fprintf(fp, "%s=%lld\n", name, config_value->value.int64_val);
                break;
            }
            case CONFIG_TYPE_UINT64:
            {
                fprintf(fp, "%s=%llu\n", name, config_value->value.uint64_val);
                break;
            }
            case CONFIG_TYPE_INT32:
            case CONFIG_TYPE_UINT31:
            {
                /*
                 * On some systems "long int" is 32 bits, on others, 64 bits.
                 * However "long long int" is always 64 bits, so just cast up.
                 */
                fprintf(fp, "%s=%lld\n", name, (int64_t)(config_value->value.int32_val));
                break;
            }
            case CONFIG_TYPE_UINT32:
            {
                fprintf(fp, "%s=%llu\n", name, (uint64_t)(config_value->value.uint32_val));
                break;
            }
            case CONFIG_TYPE_INT16:
            case CONFIG_TYPE_UINT15:
            {
                fprintf(fp, "%s=%d\n", name, config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                fprintf(fp, "%s=%u\n", name, config_value->value.uint16_val);
                break;
            }
            case CONFIG_TYPE_INT8:
            case CONFIG_TYPE_UINT7:
            {
                fprintf(fp, "%s=%d\n", name, config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                fprintf(fp, "%s=%u\n", name, config_value->value.uint8_val);
                break;
            }
            case CONFIG_TYPE_BOOL:
            {
                fprintf(fp, "%s=%s\n", name,
                        ((true == config_value->value.bool_val) ? "TRUE" : "FALSE"));
                break;
            }
            case CONFIG_TYPE_STRING:
            {
                fprintf(fp, "%s=\"", name);
                ptr = config_value->value.str_val;
                while('\0' != *ptr)
                {
                    if(('\\' == *ptr) || ('"' == *ptr))
                    {
                        (void)fputc('\\', fp);
                    }
                    (void)fputc(*ptr, fp);
                    ptr++;
                }
                fprintf(fp, "\"\n");
                break;
            }
            default:
            {
                break;
            }
        }

        config_value = (ConfigValue *)(_data->GetNextData((uint8_t **)(&name), NULL));
    }
}


int64_t ConfigManager::GetInt64(const char *name, int64_t default_val)
{
    int64_t      result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_INT64;
        config_value->value.int64_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_INT64:
            case CONFIG_TYPE_UINT63:
            {
                result = config_value->value.int64_val;
                break;
            }
            case CONFIG_TYPE_INT32:
            case CONFIG_TYPE_UINT31:
            {
                result = (int64_t)(config_value->value.int32_val);
                break;
            }
            case CONFIG_TYPE_UINT32:
            {
                result = (int64_t)(config_value->value.uint32_val);
                break;
            }
            case CONFIG_TYPE_INT16:
            case CONFIG_TYPE_UINT15:
            {
                result = (int64_t)(config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                result = (int64_t)(config_value->value.uint16_val);
                break;
            }
            case CONFIG_TYPE_INT8:
            case CONFIG_TYPE_UINT7:
            {
                result = (int64_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (int64_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


uint64_t ConfigManager::GetUint64(const char *name, uint64_t default_val)
{
    uint64_t     result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_UINT64;
        config_value->value.uint64_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_UINT64:
            {
                result = config_value->value.uint64_val;
                break;
            }
            case CONFIG_TYPE_UINT63:
            {
                result = (uint64_t)(config_value->value.int64_val);
                break;
            }
            case CONFIG_TYPE_UINT31:
            {
                result = (uint64_t)(config_value->value.int32_val);
                break;
            }
            case CONFIG_TYPE_UINT32:
            {
                result = (uint64_t)(config_value->value.uint32_val);
                break;
            }
            case CONFIG_TYPE_UINT15:
            {
                result = (uint64_t)(config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                result = (uint64_t)(config_value->value.uint16_val);
                break;
            }
            case CONFIG_TYPE_UINT7:
            {
                result = (uint64_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (uint64_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


int32_t ConfigManager::GetInt32(const char *name, int32_t default_val)
{
    int32_t      result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_INT32;
        config_value->value.int32_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_INT32:
            case CONFIG_TYPE_UINT31:
            {
                result = config_value->value.int32_val;
                break;
            }
            case CONFIG_TYPE_INT16:
            case CONFIG_TYPE_UINT15:
            {
                result = (int32_t)(config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                result = (int32_t)(config_value->value.uint16_val);
                break;
            }
            case CONFIG_TYPE_INT8:
            case CONFIG_TYPE_UINT7:
            {
                result = (int32_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (int32_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


uint32_t ConfigManager::GetUint32(const char *name, uint32_t default_val)
{
    uint32_t     result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_UINT32;
        config_value->value.uint32_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_UINT31:
            {
                result = (uint32_t)(config_value->value.int32_val);
                break;
            }
            case CONFIG_TYPE_UINT32:
            {
                result = config_value->value.uint32_val;
                break;
            }
            case CONFIG_TYPE_UINT15:
            {
                result = (uint32_t)(config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                result = (uint32_t)(config_value->value.uint16_val);
                break;
            }
            case CONFIG_TYPE_UINT7:
            {
                result = (uint32_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (uint32_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


int16_t ConfigManager::GetInt16(const char *name, int16_t default_val)
{
    int16_t      result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_INT16;
        config_value->value.int16_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_INT16:
            case CONFIG_TYPE_UINT15:
            {
                result = config_value->value.int16_val;
                break;
            }
            case CONFIG_TYPE_INT8:
            case CONFIG_TYPE_UINT7:
            {
                result = (int16_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (int16_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


uint16_t ConfigManager::GetUint16(const char *name, uint16_t default_val)
{
    uint16_t     result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_UINT16;
        config_value->value.uint16_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_UINT15:
            {
                result = (uint16_t)(config_value->value.int16_val);
                break;
            }
            case CONFIG_TYPE_UINT16:
            {
                result = config_value->value.uint16_val;
                break;
            }
            case CONFIG_TYPE_UINT7:
            {
                result = (uint16_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = (uint16_t)(config_value->value.uint8_val);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


int8_t ConfigManager::GetInt8(const char *name, int8_t default_val)
{
    int8_t       result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_INT8;
        config_value->value.int8_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_INT8:
            case CONFIG_TYPE_UINT7:
            {
                result = config_value->value.int8_val;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


uint8_t ConfigManager::GetUint8(const char *name, uint8_t default_val)
{
    uint8_t      result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_UINT8;
        config_value->value.uint8_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        switch(config_value->type)
        {
            case CONFIG_TYPE_UINT7:
            {
                result = (uint8_t)(config_value->value.int8_val);
                break;
            }
            case CONFIG_TYPE_UINT8:
            {
                result = config_value->value.uint8_val;
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return result;
}


bool ConfigManager::GetBool(const char *name, bool default_val)
{
    bool         result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_BOOL;
        config_value->value.bool_val = default_val;
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        if(CONFIG_TYPE_BOOL == config_value->type)
        {
            result = config_value->value.bool_val;
        }
    }

    return result;
}


char *ConfigManager::GetString(const char *name, char *default_val)
{
    char        *result       = default_val;
    ConfigValue *config_value;
   
    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;
        config_value->type = CONFIG_TYPE_STRING;
        config_value->value.str_val = new char [strlen(default_val) + 1];
        strcpy(config_value->value.str_val, default_val);
        if(true != _data->Add(config_value, name))
        {
            delete config_value;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            result = config_value->value.str_val;
        }
    }

    return result;
}


void ConfigManager::SetInt64(const char *name, int64_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_INT64;
        config_value->value.int64_val = value;
    }
}


void ConfigManager::SetUint64(const char *name, uint64_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_UINT64;
        config_value->value.uint64_val = value;
    }
}


void ConfigManager::SetInt32(const char *name, int32_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_INT32;
        config_value->value.int32_val = value;
    }
}


void ConfigManager::SetUint32(const char *name, uint32_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_UINT32;
        config_value->value.uint32_val = value;
    }
}


void ConfigManager::SetInt16(const char *name, int16_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_INT16;
        config_value->value.int16_val = value;
    }
}


void ConfigManager::SetUint16(const char *name, uint16_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_UINT16;
        config_value->value.uint16_val = value;
    }
}


void ConfigManager::SetInt8(const char *name, int8_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_INT8;
        config_value->value.int8_val = value;
    }
}


void ConfigManager::SetUint8(const char *name, uint8_t value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_UINT8;
        config_value->value.uint8_val = value;
    }
}


void ConfigManager::SetBool(const char *name, bool value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }
    else
    {
        if(CONFIG_TYPE_STRING == config_value->type)
        {
            delete [] config_value->value.str_val;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_BOOL;
        config_value->value.bool_val = value;
    }
}


void ConfigManager::SetString(const char *name, char *value)
{
    ConfigValue *config_value;

    config_value = (ConfigValue *)(_data->Find(name));

    if(NULL == config_value)
    {
        config_value = new ConfigValue;

        if(true != _data->Add(config_value, name))
        {
            delete config_value;
            config_value = NULL;
        }
    }

    if(NULL != config_value)
    {
        config_value->type = CONFIG_TYPE_STRING;
        config_value->value.str_val = new char [strlen(value) + 1];
        strcpy(config_value->value.str_val, value);
    }
}


