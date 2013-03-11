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
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "data_store.hpp"

#include "working_directory.hpp"


struct file_data_t
{
    char       *name;
    FILE       *read_fp;
    FILE       *write_fp;
    bool        needs_update;
    bool        lock_held;
};


WorkingDirectory *WorkingDirectory::OpenWorkingDirectory(const char *parent_path, const char *name)
{
    WorkingDirectory *dir         = NULL;
    int               rv;
    struct stat       stat_result;
    char             *full_path;

    rv = stat(parent_path, &stat_result);
    if(0 == rv)
    {
        if(S_ISDIR(stat_result.st_mode))
        {
            /* Parent path is a valid directory path. */
            full_path = new char[strlen(parent_path) + strlen(name) + 2];
            if(NULL != full_path)
            {
                sprintf(full_path, "%s/%s", parent_path, name);

                rv = stat(full_path, &stat_result);
                if(0 == rv)
                {
                    if(S_ISDIR(stat_result.st_mode))
                    {
                        dir = new WorkingDirectory(full_path);
                    }
                    else
                    {
                        delete [] full_path;
                    }
                }
                else if(ENOENT == errno)
                {
                    rv = mkdir(full_path, S_IRWXU);
                    if(0 == rv)
                    {
                        dir = new WorkingDirectory(full_path);
                    }
                    else
                    {
                        delete [] full_path;
                    }
                }
                else
                {
                    delete [] full_path;
                }
            }
        }
    }

    return dir;
}


WorkingDirectory *WorkingDirectory::OpenWorkingDirectory(const char *name)
{
    return WorkingDirectory::OpenWorkingDirectory(_path, name);
}


bool WorkingDirectory::EraseWorkingDirectory(const char *parent_path, const char *name)
{
    return WorkingDirectory::remove(parent_path, name);
}


WorkingDirectory::WorkingDirectory(const char *path)
{
    _path = path;
    _file_data = new DataStore();
}


WorkingDirectory::~WorkingDirectory()
{
    FileData file;

    file = (FileData)(_file_data->GetFirstData(NULL, NULL));

    while(NULL != file)
    {
        if(NULL != file->read_fp)
        {
            (void)CloseReadFile(file->name);
        }
        if(NULL != file->write_fp)
        {
            (void)CloseWriteFile(file->name);
        }
        if(true == file->lock_held)
        {
            (void)UnlockFile(file->name);
        }

        delete [] file->name;
        delete file;

        file = (FileData)(_file_data->GetNextData(NULL, NULL));
    }

    delete [] _path;
    delete _file_data;
}


FILE *WorkingDirectory::OpenReadFile(const char *name)
{
    FILE     *fp   = NULL;
    FileData  file = NULL;
    char     *path;

    file = get_file_data(name);
    if((NULL != file) && (NULL == file->read_fp))
    {
        path = get_full_path(name, "");
        if(NULL != path)
        {
            fp = fopen(path, "rb");
            file->read_fp = fp;

            delete [] path;
        }
    }

    return fp;
}


bool WorkingDirectory::CloseReadFile(const char *name)
{
    bool      result = false;
    FileData  file   = NULL;
    char     *path;
    char     *path_new;

    file = get_file_data(name);
    if((NULL != file) && (NULL != file->read_fp))
    {
        fclose(file->read_fp);
        file->read_fp = NULL;

        if((NULL == file->write_fp) && (true == file->needs_update))
        {
            path = get_full_path(name, "");
            if(NULL != path)
            {
                path_new = get_full_path(name, ".new");
                if(NULL != path_new)
                {
                    if(0 == rename(path_new, path))
                    {
                        /*
                         * This can fail on Windows if the file is open
                         * for reading by another instance. In such a case
                         * the .new file is left there and the file can no
                         * longer be opened for writing.
                         */
                        result = true;
                        file->needs_update = false;
                    }

                    delete [] path_new;
                }

                delete [] path;
            }
        }
        else
        {
            result = true;
        }
    }

    return result;
}


FILE *WorkingDirectory::OpenWriteFile(const char *name)
{
    FILE     *fp          = NULL;
    FileData  file        = NULL;
    bool      need_unlock = false;
    char     *path;
    int       fd;

    file = get_file_data(name);
    if((NULL != file) && (NULL == file->write_fp))
    {
        if(false == file->lock_held)
        {
            need_unlock = LockFile(name, NULL);
        }

        if(true == file->lock_held)
        {
            path = get_full_path(name, ".new");
            if(NULL != path)
            {
                fd = open(path, (O_WRONLY | O_CREAT | O_EXCL), S_IRWXU);
                if(0 < fd)
                {
                    fp = fdopen(fd, "wb");
                    file->write_fp = fp;
                }

                delete [] path;
            }
        }

        if(true == need_unlock)
        {
            (void)UnlockFile(name);
        }
    }

    return fp;
}


bool WorkingDirectory::CloseWriteFile(const char *name)
{
    bool      result = false;
    FileData  file   = NULL;
    char     *path;
    char     *path_new;

    file = get_file_data(name);
    if((NULL != file) && (NULL != file->write_fp))
    {
        fclose(file->write_fp);
        file->write_fp = NULL;

        if(NULL == file->read_fp)
        {
            path = get_full_path(name, "");
            if(NULL != path)
            {
                path_new = get_full_path(name, ".new");
                if(NULL != path_new)
                {
                    if(0 == rename(path_new, path))
                    {
                        /*
                         * This can fail on Windows if the file is open
                         * for reading by another instance. In such a case
                         * the .new file is left there and the file can no
                         * longer be opened for writing.
                         */
                        result = true;
                    }

                    delete [] path_new;
                }

                delete [] path;
            }
        }
        else
        {
            file->needs_update = true;
            result = true;
        }
    }

    return result;
}


bool WorkingDirectory::LockFile(const char *name, pid_t *pid)
{
    bool           result    = false;
    FileData       file      = NULL;
    char          *path;
    int            fd;
    FILE          *fp;
    int            i;
    unsigned char  c;
    pid_t          my_pid    = getpid();
    int            power;

    file = get_file_data(name);
    if((NULL != pid) && (NULL != file))
    {
        if(true == file->lock_held)
        {
            *pid = 0;
            result = true;
        }
        else
        {
            path = get_full_path(name, ".lock");
            if(NULL != path)
            {
                /* Loop to avoid timing issues. */
                while(true)
                {
                    fd = open(path, (O_WRONLY | O_CREAT | O_EXCL), S_IRWXU);
                    if(0 >= fd)
                    {
                        if(EEXIST == errno)
                        {
                            fp = fopen(path, "r");
                            if(NULL != fp)
                            {
                                *pid = 0;

                                i = fgetc(fp);
                                while(('0' <= i) && ('9' >= i))
                                {
                                    *pid = *pid * 10;
                                    *pid += (i - '0');
                                    i = fgetc(fp);
                                }

                                if(0 < *pid)
                                {
                                    result = true;
                                }
                                fclose(fp);
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        power = 1;
                        i = my_pid / 10;
                        while(0 < i)
                        {
                            power = power * 10;
                            i = i / 10;
                        }

                        result = true;
                        while((0 < power) && (true == result))
                        {
                            c = (char)('0' + (my_pid / power));
                            my_pid = my_pid % power;
                            power = power / 10;

                            if(1 != write(fd, &c, 1))
                            {
                                result = false;
                            }
                        }

                        close(fd);

                        if(true == result)
                        {
                            file->lock_held = true;
                            *pid = 0;
                            result = true;
                        }
                        else
                        {
                            unlink(path);
                        }
                        break;
                    }
                } /* END WHILE Looping to avoid timing issues. */
            }
        }
    }

    return result;
}


bool WorkingDirectory::UnlockFile(const char *name)
{
    bool      result = false;
    FileData  file   = NULL;
    char     *path;

    file = get_file_data(name);
    if((NULL != file) && (true == file->lock_held))
    {
        path = get_full_path(name, ".lock");
        if(NULL != path)
        {
            file->lock_held = false;
            result = (0 == unlink(path)) ? true : false;
        }
    }

    return result;
}


bool WorkingDirectory::FileExists(const char *name, bool *exists)
{
    bool         result      = false;
    char        *path;
    int          rv;
    struct stat  stat_result;

    path = get_full_path(name, "");
    if(NULL != path)
    {
        rv = stat(path, &stat_result);
        if(0 == rv)
        {
            if(S_ISDIR(stat_result.st_mode))
            {
                *exists = false; /* Not a file. */
            }
            else
            {
                *exists = true;
            }

            result = true;
        }
        else
        {
            if(ENOENT == errno)
            {
                *exists = false;
                result = true;
            }
        }
    }

    return result;
}


bool WorkingDirectory::RemoveFile(const char *name)
{
    bool         result      = false;
    pid_t        pid;
    FileData     file        = NULL;
    char        *path;
    struct stat  stat_result;

    if(true == LockFile(name, &pid))
    {
        file = get_file_data(name);
        if(NULL != file)
        {
            if(NULL != file->write_fp)
            {
                (void)CloseWriteFile(file->name);
                result = true;
            }
            else
            {
                path = get_full_path(name, ".new");
                if(NULL != path)
                {
                    if((0 != stat(path, &stat_result)) && (ENOENT == errno))
                    {
                        result = true;
                    }
                }
            }
        }

        if(true == result)
        {
            result = false;

            file = (FileData)(_file_data->Remove(name));
            if(NULL != file)
            {
                if(NULL != file->read_fp)
                {
                    (void)CloseReadFile(file->name);
                }

                /* Just in case - the file should not exist. */
                path = get_full_path(name, ".new");
                if(NULL != path)
                {
                    (void)unlink(path);
                }

                path = get_full_path(name, "");
                if(NULL != path)
                {
                    if(0 == unlink(path))
                    {
                        delete [] file->name;
                        delete file;

                        result = true;
                    }
                }

                if(false == result)
                {
                    (void)_file_data->Add(file, name);
                }
            }
        }

        if(true == result)
        {
            /*
             * If this fails we'll get a stale lock file that should get
             * deleted later. However the file has been removed so the result
             * is still "true".
             */
            path = get_full_path(name, ".lock");
            if(NULL != path)
            {
                (void)unlink(path);
            }
        }
        else
        {
            (void)UnlockFile(name);
        }
    }

    return result;
}


bool WorkingDirectory::remove(const char *parent_path, const char *name)
{
    bool           result      = false;
    char          *full_path;
    int            rv;
    struct stat    stat_result;
    DIR           *dp;
    struct dirent *dir_data;

    if(('.' != name[0]) || (('.' != name[1]) && ('\0' != name[1])))
    {
        full_path = new char[strlen(parent_path) + strlen(name) + 2];
        if(NULL != full_path)
        {
            sprintf(full_path, "%s/%s", parent_path, name);

            rv = stat(full_path, &stat_result);
            if(0 == rv)
            {
                if(S_ISDIR(stat_result.st_mode))
                {
                    dp = opendir(full_path);
                    if(NULL != dp)
                    {
                        while(NULL != (dir_data = readdir(dp)))
                        {
                            (void)remove(full_path, dir_data->d_name);
                        }

                        (void)closedir(dp);
                    }

                    result = (0 == rmdir(full_path));
                }
                else
                {
                    result = (0 == unlink(full_path));
                }
            }

            delete [] full_path;
        }
    }

    return result;
}


FileData WorkingDirectory::get_file_data(const char *name)
{
    FileData file = NULL;

    file = (FileData)(_file_data->Find(name));
    if(NULL == file)
    {
        file = new struct file_data_t;
        if(NULL != file)
        {
            file->name = new char [strlen(name) + 1];
            if(NULL == file->name)
            {
                delete file;
                file = NULL;
            }
            else
            {
                strcpy(file->name, name);
                file->read_fp = NULL;
                file->write_fp = NULL;
                file->needs_update = false;
                file->lock_held = false;

                if(false == _file_data->Add(file, name))
                {
                    delete [] file->name;
                    delete file;
                    file = NULL;
                }
            }
        }
    }

    return file;
}


char *WorkingDirectory::get_full_path(const char *name, const char *ext)
{
    char *result = NULL;

    result = new char [strlen(_path) + strlen(name) + strlen(ext) + 2];
    if(NULL != result)
    {
        sprintf(result, "%s/%s%s", _path, name, ext);
    }

    return result;
}


