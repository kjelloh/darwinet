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


int main(int argc, char **argv)
{
    int fail_count = 0U;

    fail_count += test_data_store();
    fail_count += test_working_directory();

    printf("%d test errors.\n", fail_count);

    return fail_count;
}


