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
 * This class manages multiple configuration options, loading them from file
 * and saving them to file when finished.
 *
 * Values are parsed and saved in files like:
 *
 * my_bool_value=TRUE
 * my.int.value=-45
 * a_string_value.0="Some text here"
 *
 * However the class does not support INI like sections or indexed values. The
 * class also does not support any sort of type conversion except that when
 * parsing a config file the class does not make any unsupported assumptions
 * about the data type (integer is assumed if the value begins with a - symbol,
 * bit size is assumed only where the value will not fit in a smaller size).
 * Hence such numbers can be retrieved with any appropriate data type.
 */


#ifndef _CONFIG_MANAGER_HPP_
#define _CONFIG_MANAGER_HPP_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


class DataStore;


class ConfigManager
{
public:
    ConfigManager();
    ~ConfigManager();

    /**
     * @brief Load configuration from file.
     *
     * @param[in]    fp                File to load config from.
     */
    void Load(FILE *fp);

    /**
     * @brief Save configuration to file.
     *
     * @param[in]    fp                File to save config to.
     */
    void Save(FILE *fp);

    /**
     * @brief Get a configuration value.
     *
     * If no value is found, the default value is added to the configuration
     * set. If a value of the wrong type is found then the default value is
     * returned, but the configuration set is unchanged.
     *
     * @param[in]    name              The name of the configuration value.
     * @param[in]    default_val       Default value to use.
     *
     * @return The configuration value if found and of the right type.
     * @return The default value if no value of the right type found.
     */
    int64_t GetInt64(const char *name, int64_t default_val);
    uint64_t GetUint64(const char *name, uint64_t default_val);
    int32_t GetInt32(const char *name, int32_t default_val);
    uint32_t GetUint32(const char *name, uint32_t default_val);
    int16_t GetInt16(const char *name, int16_t default_val);
    uint16_t GetUint16(const char *name, uint16_t default_val);
    int8_t GetInt8(const char *name, int8_t default_val);
    uint8_t GetUint8(const char *name, uint8_t default_val);
    bool GetBool(const char *name, bool default_val);
    char *GetString(const char *name, char *default_val);


    /**
     * @brief Set a configuration value.
     *
     * @param[in]    name              The name of the configuration value.
     * @param[in]    value             Vvalue to set.
     */
    void SetInt64(const char *name, int64_t value);
    void SetUint64(const char *name, uint64_t value);
    void SetInt32(const char *name, int32_t value);
    void SetUint32(const char *name, uint32_t value);
    void SetInt16(const char *name, int16_t value);
    void SetUint16(const char *name, uint16_t value);
    void SetInt8(const char *name, int8_t value);
    void SetUint8(const char *name, uint8_t value);
    void SetBool(const char *name, bool value);
    void SetString(const char *name, char *value);


private:
    DataStore *_data;


};


#endif /* !_CONFIG_MANAGER_HPP_ */

