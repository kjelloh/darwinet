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


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "data_store.hpp"
#include "working_directory.hpp"
#include "config_manager.hpp"


static char *test_strings[] =
{
    "Hello", "there", "everyone!", "I hope", "you", "are well", "today?"
};


static int test_data_store(void)
{
    int        fail_count   = 0;
    DataStore *datastore;
    uint32_t   string_count = sizeof(test_strings) / sizeof(*test_strings);
    uint32_t   i;
    uint32_t   data_count;
    char      *data;
    uint8_t   *key;
    uint32_t   length;
   
    datastore = new DataStore();

    for(i = 0U; i < 1024U; i++)
    {
        if(i < string_count)
        {
            if(true != datastore->Add(test_strings[i], test_strings[i]))
            {
                fprintf(stderr, "Failed to add data item '%s' to data store.\n", test_strings[i]);
                fail_count++;
            }
        }
        else
        {
            if(true != datastore->Add(test_strings[i % string_count], (uint8_t *)(&i), sizeof(uint32_t)))
            {
                fprintf(stderr, "Failed to add data item %d to data store.\n", i);
                fail_count++;
            }
        }
    }

    data_count = 0U;
    data = (char *)datastore->GetFirstData(&key, &length);
    while(NULL != data)
    {
        data_count++;

        if((length != (strlen(data) + 1)) || (0 != strcmp(data, (char *)key)))
        {
            i = *((uint32_t *)key);
            if((i >= 1024U) || (data != test_strings[i % string_count]))
            {
                fprintf(stderr, "Unrecognised data '%s' (%d) found in data store.\n", data, i);
                fail_count++;
            }
        }

        data = (char *)datastore->GetNextData(&key, &length);
    }

    if(1024U != data_count)
    {
        fprintf(stderr, "%d data items found - epxected %d.\n", data_count, 1024U);
        fail_count++;
    }

    if(NULL != datastore->Find("Hahahaha"))
    {
        fprintf(stderr, "found data item that should not be in data store.\n");
        fail_count++;
    }

    i = 2048;
    if(NULL != datastore->Find((uint8_t *)(&i), sizeof(uint32_t)))
    {
        fprintf(stderr, "found data item that should not be in data store.\n");
        fail_count++;
    }

    for(i = 0U; i < string_count; i++)
    {
        if(test_strings[i] != datastore->Remove(test_strings[i]))
        {
            fprintf(stderr, "Failed to remove data item '%s' from data store.\n", test_strings[i]);
            fail_count++;
        }
    }

    for(i = 0U; i < 1024; i++)
    {
        if(i < string_count)
        {
            if(NULL != datastore->Find(test_strings[i]))
            {
                fprintf(stderr, "Failed to remove data item '%s' from data store properly.\n", test_strings[i]);
                fail_count++;
            }
        }
        else
        {
            if(test_strings[i % string_count] != datastore->Find((uint8_t *)(&i), sizeof(uint32_t)))
            {
                fprintf(stderr, "Failed to find data item %d in data store.\n", i);
                fail_count++;
            }
        }
    }

    delete datastore;

    return fail_count;
}


static int test_working_directory(void)
{
    int               fail_count = 0;
    WorkingDirectory *wd1;
    WorkingDirectory *wd2;
    WorkingDirectory *wd3;
    pid_t             pid;
    FILE             *fp1;
    FILE             *fp2;
    bool              exists;
    char              buffer[32];

    wd1 = WorkingDirectory::OpenWorkingDirectory("/tmp", "test_dir");
    if(NULL == wd1)
    {
        fprintf(stderr, "Failed to open working directory /tmp/test_dir.\n");
        fail_count++;
    }

    wd2 = WorkingDirectory::OpenWorkingDirectory("/tmp/", "test_dir");
    if(NULL == wd2)
    {
        fprintf(stderr, "Failed to re-open working directory /tmp/test_dir.\n");
        fail_count++;
    }
    else
    {
        if(false == wd1->LockFile("lock_test", &pid))
        {
            fprintf(stderr, "LockFile() failed to execute.\n");
            fail_count++;
        }
        else if(0 != pid)
        {
            fprintf(stderr, "LockFile() failed to lock the file first time.\n");
            fail_count++;
        }
        else
        {
            if(false == wd1->LockFile("lock_test", &pid))
            {
                fprintf(stderr, "LockFile() failed to execute recursively.\n");
                fail_count++;
            }
            else
            {
                if(0 != pid)
                {
                    fprintf(stderr, "LockFile() failed to lock the file recursively.\n");
                    fail_count++;
                }
            }

            if(false == wd2->LockFile("lock_test", &pid))
            {
                fprintf(stderr, "LockFile() failed to execute for already locked file.\n");
                fail_count++;
            }
            else
            {
                if(0 == pid)
                {
                    fprintf(stderr, "LockFile() managed to lock already locked file.\n");
                    fail_count++;
                }

                if(getpid() != pid)
                {
                    fprintf(stderr, "LockFile() returned incorrect PID. Expected %d, got %d.\n",
                            getpid(), pid);
                    fail_count++;
                }
            }

            fp2 = wd2->OpenWriteFile("lock_test");
            if(NULL != fp2)
            {
                fprintf(stderr, "OpenWriteFile() opened file locked by someone else.\n");
                fail_count++;
                (void)wd2->CloseWriteFile("lock_test");
            }

            fp1 = wd1->OpenWriteFile("lock_test");
            if(NULL == fp1)
            {
                fprintf(stderr, "OpenWriteFile() failed to open file locked by self.\n");
                fail_count++;
            }

            if(false == wd1->UnlockFile("lock_test"))
            {
                fprintf(stderr, "UnlockFile() failed to execute.\n");
                fail_count++;
            }

            fp2 = wd2->OpenWriteFile("lock_test");
            if(NULL != fp2)
            {
                fprintf(stderr, "OpenWriteFile() opened file already opened for write by someone else.\n");
                fail_count++;
                (void)wd2->CloseWriteFile("lock_test");
            }

            if(false == wd2->LockFile("lock_test", &pid))
            {
                fprintf(stderr, "LockFile() failed to execute for unlocked file.\n");
                fail_count++;
            }
            else
            {
                if(0 != pid)
                {
                    fprintf(stderr, "LockFile() failed to lock unlocked file.\n");
                    fail_count++;
                }
            }

            if(true == wd1->UnlockFile("lock_test"))
            {
                fprintf(stderr, "UnlockFile() managed to unlock a file locked by someone else.\n");
                fail_count++;
            }
        }

        if(NULL != fp1)
        {
            fprintf(fp1, "%s", test_strings[0]);

            if(false == wd2->FileExists("lock_test", &exists))
            {
                fprintf(stderr, "FileExists() failed to execute.\n");
                fail_count++;
            }
            else
            {
                if(true == exists)
                {
                    fprintf(stderr, "FileExists() detected non-existent file.\n");
                    fail_count++;
                }
            }

            if(false == wd2->FileExists("lock_test.new", &exists))
            {
                fprintf(stderr, "FileExists() failed to execute.\n");
                fail_count++;
            }
            else
            {
                if(false == exists)
                {
                    fprintf(stderr, "FileExists() didn't detect file \"lock_test.new\".\n");
                    fail_count++;
                }
            }

            if(true == wd2->CloseWriteFile("lock_test"))
            {
                fprintf(stderr, "CloseWriteFile() closed write file opened by someone else.\n");
                fail_count++;
            }

            if(false == wd1->CloseWriteFile("lock_test"))
            {
                fprintf(stderr, "CloseWriteFile() failed to execute.\n");
                fail_count++;
            }

            if(false == wd2->FileExists("lock_test", &exists))
            {
                fprintf(stderr, "FileExists() failed to execute.\n");
                fail_count++;
            }
            else
            {
                if(false == exists)
                {
                    fprintf(stderr, "FileExists() didn't detect file \"lock_test\".\n");
                    fail_count++;
                }
            }
        }

        fp1 = wd2->OpenReadFile("lock_test");
        if(NULL == fp1)
        {
            fprintf(stderr, "OpenReadFile() failed to open file.\n");
            fail_count++;
        }
        else
        {
            fp2 = wd2->OpenWriteFile("lock_test");
            if(NULL == fp2)
            {
                fprintf(stderr, "OpenWriteFile() failed to open file.\n");
                fail_count++;
            }
            else
            {
                fprintf(fp2, "%s", test_strings[1]);

                if(false == wd2->CloseWriteFile("lock_test"))
                {
                    fprintf(stderr, "CloseWriteFile() failed to execute.\n");
                    fail_count++;
                }
            }

            if(NULL == fgets(buffer, 32, fp1))
            {
                fprintf(stderr, "Failed to read from file.\n");
                fail_count++;
            }
            else
            {
                if(0 != strcmp(buffer, test_strings[0]))
                {
                    fprintf(stderr, "Contents of file are not as expected.\n");
                    fail_count++;
                }
            }

            if(true == wd1->CloseReadFile("lock_test"))
            {
                fprintf(stderr, "CloseReadFile() closed read file opened by someone else.\n");
                fail_count++;
            }

            if(false == wd2->CloseReadFile("lock_test"))
            {
                fprintf(stderr, "CloseReadFile() failed to execute.\n");
                fail_count++;
            }
        }

        fp1 = wd2->OpenReadFile("lock_test");
        if(NULL == fp1)
        {
            fprintf(stderr, "OpenReadFile() failed to open file.\n");
            fail_count++;
        }
        else
        {
            if(NULL == fgets(buffer, 32, fp1))
            {
                fprintf(stderr, "Failed to read from file.\n");
                fail_count++;
            }
            else
            {
                if(0 != strcmp(buffer, test_strings[1]))
                {
                    fprintf(stderr, "Contents of file are not as expected after update.\n");
                    fail_count++;
                }
            }

            if(false == wd2->CloseReadFile("lock_test"))
            {
                fprintf(stderr, "CloseReadFile() failed to execute.\n");
                fail_count++;
            }
        }

        delete wd2;

        if(false == wd1->LockFile("lock_test", &pid))
        {
            fprintf(stderr, "LockFile() failed to execute for file unlocked by instance deletion.\n");
            fail_count++;
        }
        else if(0 != pid)
        {
            fprintf(stderr, "LockFile() failed to lock the file unlocked by instance deletion.\n");
            fail_count++;
        }
        else
        {
            if(false == wd1->UnlockFile("lock_test"))
            {
                fprintf(stderr, "UnlockFile() failed to execute.\n");
                fail_count++;
            }
        }
    }

    wd2 = wd1->OpenWorkingDirectory("sub_1");
    if(NULL == wd2)
    {
        fprintf(stderr, "Failed to open working directory /tmp/test_dir/sub_1.\n");
        fail_count++;
    }
    else
    {
        wd3 = wd2->OpenWorkingDirectory("/sub_2/");
        if(NULL == wd3)
        {
            fprintf(stderr, "Failed to open working directory /tmp/test_dir/sub_1/sub_2.\n");
            fail_count++;
        }
        else
        {
            delete wd3;
        }



        delete wd2;
    }


    if(NULL != wd1)
    {
        delete wd1;
    }

    if(true != WorkingDirectory::EraseWorkingDirectory("/tmp", "test_dir"))
    {
        fprintf(stderr, "Failed to remove working directory /tmp/test_dir.\n");
        fail_count++;
    }

    return fail_count;
}


static int test_config_manager(void)
{
    int            fail_count = 0;
    ConfigManager *config = new ConfigManager();
    FILE          *fp;
    uint64_t       uint64_val;
    bool           bool_val;
    char          *str_val;

    fp = fopen("test.cfg", "rb");
    if(NULL == fp)
    {
        fprintf(stderr, "Failed to open config manager test config file.\n");
        fail_count++;
    }
    else
    {
        config->Load(fp);
        fclose(fp);

        /* Test GetInt64() */
        if(13245 != config->GetInt64("Big_integer", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(13245 != config->GetInt64("test_bool", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245 != config->GetInt64("test_string", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(-13245 != config->GetInt64("new_int64", -13245))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(-13245 != config->GetInt64("new_int64", 44445))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(-654321 != config->GetInt64("integer", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        if(64 != config->GetInt64("small_uint", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetUint64() */
        /*
         * Assigning a 64 bit number to a 64 bit value appears to be too much
         * for the compiler!! Need to set 9223372040319552154 as in the test
         * config file.
         */
        uint64_val = 0x80000000U;
        uint64_val = uint64_val << 32;
        uint64_val |= 0xCE844A9AU;

        if(uint64_val != config->GetUint64("Big_integer", 13245U))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        if(13245U != config->GetUint64("test_bool", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245U != config->GetUint64("test_string", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(678901234U != config->GetUint64("new_uint64", 678901234U))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(678901234U != config->GetUint64("new_uint64", 44445U))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(13245U != config->GetUint64("integer", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type integer.\n");
            fail_count++;
        }

        if(64U != config->GetUint64("small_uint", 13245U))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetInt32() */
        if(13245 != config->GetInt32("Big_integer", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(13245 != config->GetInt32("test_bool", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245 != config->GetInt32("test_string", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(-56789 != config->GetInt32("new_int32", -56789))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(-56789 != config->GetInt32("new_int32", 44445))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(-654321 != config->GetInt32("integer", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        if(64 != config->GetInt32("small_uint", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetUint32() */
        if(13245U != config->GetUint32("Big_integer", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(13245U != config->GetUint32("test_bool", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245U != config->GetUint32("test_string", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(98765U != config->GetUint32("new_uint32", 98765U))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(98765U != config->GetUint32("new_uint32", 44445U))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(13245U != config->GetUint32("integer", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        if(64U != config->GetUint32("small_uint", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetInt16() */
        if(13245 != config->GetInt16("Big_integer", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(13245 != config->GetInt16("test_bool", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245 != config->GetInt16("test_string", 13245))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(-3456 != config->GetInt16("new_int16", -3456))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(-3456 != config->GetInt16("new_int16", 1234))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(4567 != config->GetInt16("integer", 4567))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        if(64 != config->GetInt16("small_uint", 13245))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetUint16() */
        if(13245U != config->GetUint16("Big_integer", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(13245U != config->GetUint16("test_bool", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(13245U != config->GetUint16("test_string", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(4321U != config->GetUint16("new_uint16", 4321U))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(4321U != config->GetUint16("new_uint16", 13245U))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(13245U != config->GetUint16("integer", 13245U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        if(64U != config->GetUint16("small_uint", 13245U))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetInt8() */
        if(56 != config->GetInt8("Big_integer", 56))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(56 != config->GetInt8("test_bool", 56))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(56 != config->GetInt8("test_string", 56))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(-23 != config->GetInt8("new_int8", -23))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(-23 != config->GetInt8("new_int8", 120))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(56 != config->GetInt8("integer", 56))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        if(64 != config->GetInt8("small_uint", 56))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetUint8() */
        if(56U != config->GetUint8("Big_integer", 56U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type uint64.\n");
            fail_count++;
        }

        if(56U != config->GetUint8("test_bool", 56U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        if(56U != config->GetUint8("test_string", 56U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        if(41U != config->GetUint8("new_uint8", 41U))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        if(41U != config->GetUint8("new_uint8", 56U))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        if(56U != config->GetUint8("small_int", 56U))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int8.\n");
            fail_count++;
        }

        if(64U != config->GetUint8("small_uint", 56U))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetBool() */
        bool_val = config->GetBool("integer", true);
        if(true != bool_val)
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        bool_val = config->GetBool("test_string", false);
        if(false != bool_val)
        {
            fprintf(stderr, "Didn't use default value for incompatible type string.\n");
            fail_count++;
        }

        bool_val = config->GetBool("new_bool", false);
        if(false != bool_val)
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        bool_val = config->GetBool("new_bool", true);
        if(false != bool_val)
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        bool_val = config->GetBool("test_bool", true);
        if(false != bool_val)
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        bool_val = config->GetBool("is_true", false);
        if(true != bool_val)
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        /* Test GetString() */
        str_val = config->GetString("integer", "Hello");
        if(0 != strcmp(str_val, "Hello"))
        {
            fprintf(stderr, "Didn't use default value for incompatible type int32.\n");
            fail_count++;
        }

        str_val = config->GetString("test_bool", "Hello");
        if(0 != strcmp(str_val, "Hello"))
        {
            fprintf(stderr, "Didn't use default value for incompatible type bool.\n");
            fail_count++;
        }

        str_val = config->GetString("new_string", "World");
        if(0 != strcmp(str_val, "World"))
        {
            fprintf(stderr, "Didn't use default value for new config.\n");
            fail_count++;
        }

        str_val = config->GetString("new_string", "Cowabunga!");
        if(0 != strcmp(str_val, "World"))
        {
            fprintf(stderr, "Didn't get actual value for newly added config.\n");
            fail_count++;
        }

        str_val = config->GetString("test_string", "Hello");
        if(0 != strcmp(str_val, "This isn't a very long test string, \"boy\"."))
        {
            fprintf(stderr, "Didn't get actual value for compatible type.\n");
            fail_count++;
        }

        config->SetInt64("test_bool", 456346546);
        uint64_val = 0x00011C12;
        uint64_val = uint64_val << 32;
        uint64_val |= 0xE51AC439;
        config->SetUint64("is_true", uint64_val);
        config->SetInt32("misc_int", 3464676);
        config->SetUint32("blahblah", 54767734U);
        config->SetInt16("Big_integer", -4096);
        config->SetUint16("integer", 2363U);
        config->SetInt8("test_string", -54);
        config->SetUint8("byte_val", 160U);
        config->SetBool("small_int", false);
        config->SetString("small_uint", "Muahahaha");
    }

    fp = fopen("/tmp/new.cfg", "wb");
    if(NULL == fp)
    {
        fprintf(stderr, "Failed to open new config manager test config file.\n");
        fail_count++;
    }
    else
    {
        config->Save(fp);
        fclose(fp);

        delete config;
        config = new ConfigManager();

        fp = fopen("/tmp/new.cfg", "rb");
        if(NULL == fp)
        {
            fprintf(stderr, "Failed to open config manager test config file.\n");
            fail_count++;
        }
        else
        {
            config->Load(fp);
            fclose(fp);

            if(-13245 != config->GetInt64("new_int64", 44445))
            {
                fprintf(stderr, "Didn't get actual value for previously added int64 config.\n");
                fail_count++;
            }

            if(678901234U != config->GetUint64("new_uint64", 44445U))
            {
                fprintf(stderr, "Didn't get actual value for previously added uint64 config.\n");
                fail_count++;
            }

            if(-56789 != config->GetInt32("new_int32", 44445))
            {
                fprintf(stderr, "Didn't get actual value for previously added int32 config.\n");
                fail_count++;
            }

            if(98765U != config->GetUint32("new_uint32", 44445U))
            {
                fprintf(stderr, "Didn't get actual value for previously added uint32 config.\n");
                fail_count++;
            }

            if(-3456 != config->GetInt16("new_int16", 1234))
            {
                fprintf(stderr, "Didn't get actual value for previously added int16 config.\n");
                fail_count++;
            }

            if(4321U != config->GetUint16("new_uint16", 13245U))
            {
                fprintf(stderr, "Didn't get actual value for previously added uint16 config.\n");
                fail_count++;
            }

            if(-23 != config->GetInt8("new_int8", -120))
            {
                fprintf(stderr, "Didn't get actual value for previously added int8 config.\n");
                fail_count++;
            }

            if(41U != config->GetUint8("new_uint8", 56U))
            {
                fprintf(stderr, "Didn't get actual value for previously added uint8 config.\n");
                fail_count++;
            }

            bool_val = config->GetBool("new_bool", true);
            if(false != bool_val)
            {
                fprintf(stderr, "Didn't get actual value for previously added bool config.\n");
                fail_count++;
            }

            str_val = config->GetString("new_string", "Cowabunga!");
            if(0 != strcmp(str_val, "World"))
            {
                fprintf(stderr, "Didn't get actual value for previously added string config.\n");
                fail_count++;
            }

            if(456346546 != config->GetInt64("test_bool", 44445))
            {
                fprintf(stderr, "Didn't get actual value for updated int64 config.\n");
                fail_count++;
            }

            if(uint64_val != config->GetUint64("is_true", 44445U))
            {
                fprintf(stderr, "Didn't get actual value for updated uint64 config.\n");
                fail_count++;
            }

            if(3464676 != config->GetInt32("misc_int", 44445))
            {
                fprintf(stderr, "Didn't get actual value for updated int32 config.\n");
                fail_count++;
            }

            if(54767734U != config->GetUint32("blahblah", 44445U))
            {
                fprintf(stderr, "Didn't get actual value for updated uint32 config.\n");
                fail_count++;
            }

            if(-4096 != config->GetInt16("Big_integer", 1234))
            {
                fprintf(stderr, "Didn't get actual value for updated int16 config.\n");
                fail_count++;
            }

            if(2363U != config->GetUint16("integer", 13245U))
            {
                fprintf(stderr, "Didn't get actual value for updated uint16 config.\n");
                fail_count++;
            }

            if(-54 != config->GetInt8("test_string", -120))
            {
                fprintf(stderr, "Didn't get actual value for updated int8 config.\n");
                fail_count++;
            }

            if(160U != config->GetUint8("byte_val", 56U))
            {
                fprintf(stderr, "Didn't get actual value for updated uint8 config.\n");
                fail_count++;
            }

            bool_val = config->GetBool("small_int", true);
            if(false != bool_val)
            {
                fprintf(stderr, "Didn't get actual value for updated bool config.\n");
                fail_count++;
            }

            str_val = config->GetString("small_uint", "Cowabunga!");
            if(0 != strcmp(str_val, "Muahahaha"))
            {
                fprintf(stderr, "Didn't get actual value for updated string config.\n");
                fail_count++;
            }
        }
    }

    delete config;

    return fail_count;
}


int main(int argc, char **argv)
{
    int fail_count = 0U;

    fail_count += test_data_store();
    fail_count += test_working_directory();
    fail_count += test_config_manager();

    printf("%d test errors.\n", fail_count);

    return fail_count;
}


