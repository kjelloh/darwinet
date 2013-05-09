#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <gcrypt.h>

#include "working_directory.hpp"

#include "auth_manager.hpp"


AuthManager::AuthManager(WorkingDirectory *dir, const char *password)
{
    uint8_t   salt[8];
    uint8_t   key[32];
    uint32_t  pass_len;

    _dir = dir;

    _private_key = NULL;
    _public_key = NULL;

    if(0 == gcry_control(GCRYCTL_INITIALIZATION_FINISHED_P))
    {
        if(NULL != gcry_check_version(NULL))
        {
#ifdef USE_SECURE_MEMORY
            gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
            gcry_control(GCRYCTL_INIT_SECMEM, 16384, 0);
            gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
#else
            gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
#endif

            gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
        }
    }

    if((NULL == password) || (0 != gcry_cipher_open(&_cipher, GCRY_CIPHER_TWOFISH, GCRY_CIPHER_MODE_ECB, GCRY_CIPHER_SECURE)))
    {
        _cipher = NULL;
    }
    else
    {
        pass_len = strlen(password);

        salt[0] = pass_len & 0xFFU;
        salt[1] = (uint8_t)(password[0]);
        salt[2] = (uint8_t)(password[pass_len - 1]);
        salt[3] = (uint8_t)(password[pass_len / 2]);
        salt[4] = (uint8_t)(salt[0] ^ salt[1]);
        salt[5] = (uint8_t)(salt[2] ^ salt[3]);
        salt[6] = (uint8_t)(salt[0] ^ salt[3]);
        salt[7] = (uint8_t)(salt[2] ^ salt[1]);

        if((0 != gcry_kdf_derive(password, pass_len, GCRY_KDF_ITERSALTED_S2K, GCRY_MD_SHA256, salt, 8, 65536, 32, key)) ||
           (0 != gcry_cipher_setkey(_cipher, key, 32)))
        {
            gcry_cipher_close(_cipher);
            _cipher = NULL;
        }
    }
}


AuthManager::~AuthManager()
{
    _free_key_pair();
    gcry_cipher_close(_cipher);
}


bool AuthManager::CreateKeyPair()
{
    bool         result     = false;
    gcry_sexp_t  key_params;
    gcry_sexp_t  new_keys;

    _free_key_pair();

    if(0 == gcry_sexp_new(&key_params, "(genkey (dsa (nbits 4:1024)))", 0, 1))
    {
        if(0 == gcry_pk_genkey(&new_keys, key_params))
        {
            _private_key = gcry_sexp_find_token(new_keys, "private-key", 0);
            _public_key = gcry_sexp_find_token(new_keys, "public-key", 0);

            if((NULL != _private_key) && (NULL != _public_key))
            {
                result = true;
            }
            else
            {
                if(NULL != _private_key)
                {
                    gcry_sexp_release(_private_key);
                    _private_key = NULL;
                }

                if(NULL != _public_key)
                {
                    gcry_sexp_release(_public_key);
                    _public_key = NULL;
                }
            }

            gcry_sexp_release(new_keys);
        }

        gcry_sexp_release(key_params);
    }

    return result;
}


bool AuthManager::SaveKeyPair(const char *filename)
{
    bool      result    = false;
    FILE     *fp;
    char     *buffer;
    size_t    len;
    uint32_t  len_value;

    if((NULL != _cipher) && (NULL != _private_key) && (NULL != _public_key))
    {
        fp = _dir->OpenWriteFile(filename);
        if(NULL != fp)
        {
            len = gcry_sexp_sprint(_private_key, GCRYSEXP_FMT_CANON, NULL, 0);
            if(0U != (len % 32U))
            {
                len += len % 32U;
            }
            buffer = new char [len];
            memset(buffer, 0, len);
            (void)gcry_sexp_sprint(_private_key, GCRYSEXP_FMT_CANON, buffer, len);

            if((0 == gcry_cipher_reset(_cipher)) && (0 == gcry_cipher_encrypt(_cipher, buffer, len, NULL, 0)))
            {
                len_value = htonl(len);
                if((1 == fwrite(&len_value, sizeof(uint32_t), 1, fp)) &&
                   (len == fwrite(buffer, 1, len, fp)))
                {
                    result = true;
                }
            }

            delete [] buffer;

            if(true == result)
            {
                result = false;

                len = gcry_sexp_sprint(_public_key, GCRYSEXP_FMT_CANON, NULL, 0);
                buffer = new char [len];
                (void)gcry_sexp_sprint(_public_key, GCRYSEXP_FMT_CANON, buffer, len);

                len_value = htonl(len);
                if((1 == fwrite(&len_value, sizeof(uint32_t), 1, fp)) &&
                   (len == fwrite(buffer, 1, len, fp)))
                {
                    result = true;
                }

                delete [] buffer;
            }

            /*
             * It would be better here to implement a rollback function. On failure
             * leave the existing read file alone and just delete the write file.
             * Only keep the write file on success.
             */
            (void)_dir->CloseWriteFile(filename);

            if(false == result)
            {
                (void)_dir->RemoveFile(filename);
            }
        }
    }

    return result;
}


void AuthManager::_free_key_pair()
{
    if(NULL != _private_key)
    {
        gcry_sexp_release(_private_key);
        _private_key = NULL;
    }

    if(NULL != _public_key)
    {
        gcry_sexp_release(_public_key);
        _public_key = NULL;
    }
}


