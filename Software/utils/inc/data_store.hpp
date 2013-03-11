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
 * This class manages a hash table based data store with both lookup and
 * sequential unsorted iterator style access to the data.
 */


#ifndef _DATA_STORE_HPP_
#define _DATA_STORE_HPP_


#include <stdint.h>
#include <stdbool.h>


typedef struct data_element_t *DataElement;


class DataStore
{
public:
    DataStore();
    ~DataStore();


    /**
     * @brief Add a data element to the data store.
     *
     * Note that the calling code is still responsible for freeing the memory
     * stored in the data store.
     *
     * @param[in]    data              Data to store.
     * @param[in]    key               Key to store data with.
     * @param[in]    length            Length of key data.
     *
     * @retval True on success.
     * @retval False on failure.
     */
    bool Add(void *data, const char *key);
    bool Add(void *data, uint8_t *key, uint32_t length);

    /**
     * @brief Find an element in the data store by key.
     *
     * @param[in]    key               Key to find data with.
     * @param[in]    length            Length of key data.
     *
     * @return The data associated with the key on success.
     * @retval NULL on failure.
     */
    void *Find(const char *key);
    void *Find(uint8_t *key, uint32_t length);

    /**
     * @brief Remove an element from the data store.
     *
     * @param[in]    key               Key to find data with.
     * @param[in]    length            Length of key data.
     *
     * @return The data associated with the key on success.
     * @retval NULL on failure.
     */
    void *Remove(const char *key);
    void *Remove(uint8_t *key, uint32_t length);

    /**
     * @brief Iterator interface onto data store.
     *
     * Since all keys are stored as a byte array regardless of whether a string
     * or byte array was originally used to add the data item, a byte array is
     * what is returned in the output parameters. However the byte array (and
     * length value) include the NULL terminator when a string was used to add
     * a data item.
     *
     * The "key" and "length" parameters may be NULL. If the "key" parameter is
     * NULL then the length parameter is not used.
     *
     * Adding and removing items from the data store while simultaneously
     * using the iterator interface may result in undefined behaviour.
     *
     * @param[out]   key               Key for found element.
     * @param[out]   length            Length of key for found element.
     *
     * @return Data item from data store if there are any left.
     * @return NULL if no more data items are available to be returned.
     */
    void *GetFirstData(uint8_t **key, uint32_t *length);
    void *GetNextData(uint8_t **key, uint32_t *length);

private:
    bool         add(DataElement element, DataElement *table, uint32_t table_size);
    void         remove(DataElement element, DataElement *table, uint32_t index);
    void        *find(uint8_t *key, uint32_t length, bool remove_data);
    uint32_t     get_hash(uint8_t *key, uint32_t length);
    void         grow();

    DataElement *_data_table;
    uint32_t     _table_size;
    uint32_t     _data_count;
    uint32_t     _iterator_index;
    DataElement  _iterator_item;

};


#endif /* !_DATA_STORE_HPP_ */

