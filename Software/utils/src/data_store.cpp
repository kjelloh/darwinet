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
#include <stdint.h>
#include <stdbool.h>

#include "data_store.hpp"


#define HASH_START_SIZE         (31U)
#define HASH_CHUNK_SIZE         (512U)
#define HASH_SIZE_DOUBLE_LIMIT  (1024U)


struct data_element_t
{
    struct data_element_t *prev;
    struct data_element_t *next;
    uint8_t               *key;
    uint32_t               key_length;
    void                  *data;
};


DataStore::DataStore()
{
    _table_size = HASH_START_SIZE;
    _data_table = new DataElement[_table_size];

    if(NULL == _data_table)
    {
        _table_size = 0U;
    }
    else
    {
        memset(_data_table, 0, (sizeof(DataElement) * _table_size));
    }

    _data_count = 0U;
}


DataStore::~DataStore()
{
    uint32_t     i;
    DataElement  element;
    DataElement  next;

    for(i = 0U; i < _table_size; i++)
    {
        element = _data_table[i];
        while(NULL != element)
        {
            next = element->next;
            delete [] element->key;
            delete element;
            element = next;
        }
    }

    delete [] _data_table;
}


bool DataStore::Add(void *data, const char *key)
{
    return Add(data, (uint8_t *)key, (strlen(key) + 1));
}


bool DataStore::Add(void *data, uint8_t *key, uint32_t length)
{
    bool        result  = false;
    DataElement element = NULL;

    if(_data_count >= _table_size)
    {
        grow();
    }

    element = new struct data_element_t;
    if(NULL != element)
    {
        element->prev = NULL;
        element->next = NULL;
        element->key = new uint8_t[length];
        if(NULL == element->key)
        {
            delete element;
        }
        else
        {
            memcpy(element->key, key, length);
            element->key_length = length;
            element->data = data;

            result = add(element, _data_table, _table_size);

            if(true == result)
            {
                _data_count++;
            }
            else
            {
                delete [] element->key;
                delete element;
            }
        }
    }

    return result;
}


void *DataStore::Find(const char *key)
{
    return find((uint8_t *)key, (strlen(key) + 1), false);
}


void *DataStore::Find(uint8_t *key, uint32_t length)
{
    return find(key, length, false);
}


void *DataStore::Remove(const char *key)
{
    return find((uint8_t *)key, (strlen(key) + 1), true);
}


void *DataStore::Remove(uint8_t *key, uint32_t length)
{
    return find(key, length, true);
}


void *DataStore::GetFirstData(uint8_t **key, uint32_t *length)
{
    _iterator_index = 0U;
    _iterator_item = _data_table[0];

    return GetNextData(key, length);
}


void *DataStore::GetNextData(uint8_t **key, uint32_t *length)
{
    void *data = NULL;

    while((_iterator_index < _table_size) && (NULL == _iterator_item))
    {
        _iterator_index++;
        _iterator_item = _data_table[_iterator_index];
    }

    if((_iterator_index < _table_size) && (NULL != _iterator_item))
    {
        data = _iterator_item->data;
        if(NULL != key)
        {
            *key = _iterator_item->key;
        }
        if(NULL != length)
        {
            *length = _iterator_item->key_length;
        }

        _iterator_item = _iterator_item->next;
    }

    return data;
}


bool DataStore::add(DataElement element, DataElement *table, uint32_t table_size)
{
    bool      result = false;
    uint32_t  index;

    if(0U < table_size)
    {
        result = true;

        index = get_hash(element->key, element->key_length) % table_size;

        element->prev = NULL;
        element->next = table[index];
        table[index] = element;

        if(NULL != element->next)
        {
            element->next->prev = element;
        }
    }

    return result;
}


void DataStore::remove(DataElement element, DataElement *table, uint32_t index)
{
    if(NULL != element->next)
    {
        element->next->prev = element->prev;
    }
    if(NULL != element->prev)
    {
        element->prev->next = element->next;
    }
    else if((NULL != table) && (element == table[index]))
    {
        table[index] = element->next;
    }
    else
    {
        /* Element is not in this table. This should never happen. */
    }

    element->prev = NULL;
    element->next = NULL;
}


void *DataStore::find(uint8_t *key, uint32_t length, bool remove_data)
{
    void        *data    = NULL;
    uint32_t     index;
    DataElement  element;

    if(0U < _table_size)
    {
        index = get_hash(key, length) % _table_size;
        element = _data_table[index];

        while(NULL != element)
        {
            if((element->key_length == length) && (0 == memcmp(element->key, key, length)))
            {
                data = element->data;
                if(true == remove_data)
                {
                    remove(element, _data_table, index);
                }
                break;
            }

            element = element->next;
        }
    }

    return data;
}


uint32_t DataStore::get_hash(uint8_t *key, uint32_t length)
{
    uint32_t  hash = 0U;
    uint32_t  i;
    uint32_t  byte;

    for(i = 0U; i < length; i++)
    {
        byte = (uint32_t)(key[i]) ^ (hash >> 31);
        hash = (hash << 1) ^ byte;
    }

    return hash;
}


void DataStore::grow()
{
    uint32_t     new_size;
    DataElement *new_table;
    uint32_t     i;
    DataElement  element;
    DataElement  next;

    if(HASH_SIZE_DOUBLE_LIMIT > _table_size)
    {
        new_size = (_table_size * 2) - 1;
    }
    else
    {
        new_size = _table_size + HASH_CHUNK_SIZE;
    }

    new_table = new DataElement[new_size];
    if(NULL != new_table)
    {
        memset(new_table, 0, (sizeof(DataElement) * new_size));

        for(i = 0U; i < _table_size; i++)
        {
            element = _data_table[i];
            while(NULL != element)
            {
                next = element->next;

                /* Add can only fail if the table size is zero. */
                remove(element, _data_table, i);
                (void)add(element, new_table, new_size);

                element = next;
            }
        }

        delete [] _data_table;
        _data_table = new_table;
        _table_size = new_size;
    }
}


