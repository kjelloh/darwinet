#ifndef _AUTH_MANAGER_HPP_
#define _AUTH_MANAGER_HPP_


#include <gcrypt.h>


class WorkingDirectory;


class AuthManager
{
public:
    AuthManager(WorkingDirectory *dir, const char *password);
    ~AuthManager();

    bool CreateKeyPair();
    bool SaveKeyPair(const char *filename);


private:
    void _free_key_pair();

    WorkingDirectory *_dir;
    gcry_cipher_hd_t  _cipher;
    gcry_sexp_t       _private_key;
    gcry_sexp_t       _public_key;

};


#endif /* !_AUTH_MANAGER_HPP_ */

