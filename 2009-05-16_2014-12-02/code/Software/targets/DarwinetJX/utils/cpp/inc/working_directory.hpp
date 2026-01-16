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
 * This class manages a set of files in a working directory. The instances are
 * created using factory functions to allow success or failure to be
 * determined by the return value. If a directory for which a WorkingDirectory
 * instance is requested does not exist it will be created.
 *
 * The semantics of updating (opening a file for writing) are as follows:
 *
 *   1) A new file with a ".new" extension is created if no file with the same
 *      name already exists.
 *   2) When the "write" file is closed, the "read" file handle is checked. If
 *      there is a read file open then the file is marked as needing updating,
 *      otherwise the ".new" file replaces the actual file.
 *   3) When a "read" file is closed, the flags are checked to see if the file
 *      needs an update, and if so then the ".new" file replaces the actual
 *      file.
 *
 * The result of this is that if a "read" file is open and a "write" file is
 * opened and closed, it cannot be opened again until the "read" file has been
 * closed. In addition any other processes (or duplicate working directory
 * instances) will also be so blocked. However beware that if another process
 * (or duplicate working directory instance) has a file opened for reading that
 * needs updating by the current instance, when the current instance closes the
 * "read" file the behaviour of the file in the other process or instance is
 * undefined.
 *
 * This class supports lock files. When "locking" a file, the class attempts to
 * open a file with the name and the ".lock" extension if no other lock file
 * with the same full name exists. If such a lock file already exists then the
 * lock function fails and reports that the file is already locked. The
 * equivalent unlock API just deletes the lock file. Checking if a lock file
 * exists is not reliable as the lock file may be deleted by another thread or
 * process after the lock file is detected but before the fact is acted on. The
 * only sure way to determine that a file is locked is to lock it.
 *
 * When deleting an instance of this class, all file handles will be closed
 * (and updates performed as required) and all lock files created by the
 * instance will be deleted, effectively unlocking the file.
 */


#ifndef _WORKING_DIRECTORY_HPP_
#define _WORKING_DIRECTORY_HPP_


#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


typedef struct file_data_t *FileData;


class DataStore;


class WorkingDirectory
{
public:

    /**
     * @brief Open a working directory.
     *
     * This function creates a WorkingDirectory instance for a directory.
     *
     * @param[in]    parent_path       Path of parent directory in which the
     *                                 working directory exists.
     * @param[in]    name              Name of working directory.
     *
     * @return A pointer to the WorkingDirectory instance created on success.
     * @retval NULL on failure.
     */
    static WorkingDirectory *OpenWorkingDirectory(const char *parent_path, const char *name);
    WorkingDirectory *OpenWorkingDirectory(const char *name);


    /**
     * @brief Remove a working directory and all files and directories in it.
     *
     * @param[in]    parent_path       Path of parent directory in which the
     *                                 working directory exists.
     * @param[in]    name              Name of working directory.
     *
     * @retval True on success.
     * @retval False on failure.
     */
    static bool EraseWorkingDirectory(const char *parent_path, const char *name);

    ~WorkingDirectory();

    /**
     * @brief Open a file for reading.
     *
     * @param[in]    name              Name of the file to open.
     *
     * @return File pointer to read from on success.
     * @retval NULL if the file has already been opened for reading by this
     *         instance.
     * @retval NULL if the file does not exist.
     * @retval NULL if the operation fails for some other reason.
     */
    FILE *OpenReadFile(const char *name);

    /**
     * @brief Close a file that was opened for reading.
     *
     * @param[in]    name              Name of the file to close.
     *
     * @retval True if the file was closed.
     * @retval False if the file was not already opened or closing it failed.
     */
    bool CloseReadFile(const char *name);

    /**
     * @brief Open a file for writing.
     *
     * See general class comments. The actual file will not be updated until
     * the write handle and the read handle (if open in the same instance) are
     * closed.
     *
     * It is not possible to open a file which is locked or for which a ".new"
     * file already exists.
     *
     * @param[in]    name              Name of the file to open.
     *
     * @return File pointer to write to on success.
     * @retval NULL if the file has already been opened for writing.
     * @retval NULL if the file is locked by a different instance.
     * @retval NULL if the operation fails for some other reason.
     */
    FILE *OpenWriteFile(const char *name);

    /**
     * @brief Close a file that was opened for writing.
     *
     * @param[in]    name              Name of the file to close.
     *
     * @retval True if the file was closed.
     * @retval False if the file was not already opened or closing it failed.
     */
    bool CloseWriteFile(const char *name);

    /**
     * @brief Lock a file.
     *
     * Locking a file prevents it being opened for writing by a different
     * instance and prevents it being locked by another instance. The file
     * being "locked" does not have to exist. Lock files can exist and operate
     * a locking mechanism in and of themselves without requiring a
     * corresponding data file.
     *
     * If the function returns "true", the "pid" value must be checked to see
     * if the lock was successful. If the "pid" value is 0 then the lock is
     * now held by the current instance.
     *
     * Note that the file may already be opened for writing by a different
     * instance, and locking will still succeed. If a file is to use locking
     * semantics, then all code that writes to it should lock it before
     * opening the file for writing.
     *
     * @param[in]    name              Name of the file to lock.
     * @param[out]   pid               PID of the process that has already
     *                                 locked the file if any, or 0 if none.
     *
     * @retval True if the function was successful.
     * @retval False if the function failed.
     */
    bool LockFile(const char *name, pid_t *pid);

    /**
     * @brief Unlock a file.
     *
     * This function will delete a lock file if the this instance holds the
     * lock on the file.
     *
     * @param[in]    name              Name of the file to unlock.
     *
     * @retval True if the file was successfully unlocked.
     * @retval False if the file was not locked.
     * @retval False if the lock was not held by this instance.
     * @retval False if the function failed.
     */
    bool UnlockFile(const char *name);

    /**
     * @brief Check if a file exists.
     *
     * Note that the existence or otherwise of a file may change between the
     * file being checked and the function returning or the calling code
     * processing the return value. Use of locking may solve this issue.
     *
     * @param[in]    name              Name of the file to unlock.
     * @param[out]   exists            Indicates if the file was found to exist.
     *
     * @retval True if the function succeeded.
     * @retval False if the function failed.
     */
    bool FileExists(const char *name, bool *exists);

    /**
     * @brief Remove a file.
     *
     * This function will not remove a file if it detects a lock file or a
     * write file created by another instance. It will close any file
     * handles open in this instance for the file and delete any lock files
     * this instance created.
     *
     * @param[in]    name              Name of the file to remove.
     *
     * @retval True if the file was removed.
     * @retval False if the file could not be removed (locked or being written
     *         to by another process).
     * @retval False if the function failed.
     */
    bool RemoveFile(const char *name);

private:

    WorkingDirectory(const char *path);

    static bool  remove(const char *parent_path, const char *name);
    FileData     get_file_data(const char *name);
    char        *get_full_path(const char *name, const char *ext);

    const char  *_path;
    DataStore   *_file_data;
};


#endif /* !_WORKING_DIRECTORY_HPP_ */

