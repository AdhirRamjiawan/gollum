
#include "Encrypt.h"

Encrypt::Encrypt()
{
    /* A 256 bit key */ // CHANGE THESE TO BE ENV VARS OR SOMETHING ELSE
    this->ENCRYPTION_KEY = (unsigned char*)"01234567890123456789012345678901";

    /* A 128 bit IV */ // CHANGE THESE TO BE ENV VARS OR SOMETHING ELSE
    this->ENCRYPTION_IV = (unsigned char*)"0123456789012345";
}

string Encrypt::EncryptString(string plainText)
{
    unsigned char ciphertext[MAX_FILESTORE_SIZE_IN_CHARS] = "";
    int plaintext_len = strlen(plainText.c_str());

    auto ciphertext_len = this->InternalEncrypt(
        (unsigned char*)plainText.c_str(),
        plaintext_len,
        ENCRYPTION_KEY,
        ENCRYPTION_IV, ciphertext);

    if (ciphertext_len > -1)
    {
        return string((char*)ciphertext);
    }

    return string();
}

string Encrypt::DecryptString(string encryptedText)
{
    unsigned char decryptedtext[MAX_FILESTORE_SIZE_IN_CHARS] = "";

    int decryptedtext_len = 0;
    int ciphertext_len = strlen(encryptedText.c_str());

    //BIO_dump_fp(stdout, encryptedText.c_str(), ciphertext_len);

    decryptedtext_len = this->InternalDecrypt(
        (unsigned char*)encryptedText.c_str(),
        ciphertext_len,
        ENCRYPTION_KEY,
        ENCRYPTION_IV, decryptedtext);

    if (decryptedtext_len > 0)
    {
        decryptedtext[decryptedtext_len] = '\0';
        return string((char*)decryptedtext);
    }
    
    return string();
}


int Encrypt::InternalEncrypt(unsigned char* plaintext, int plaintext_len, unsigned char* key,
    unsigned char* iv, unsigned char* ciphertext)
{
    EVP_CIPHER_CTX* ctx;
    int len, ciphertext_len;


    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        cerr << "error getting cipher context" << endl;
        return -1;
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        cerr << "error evp_encryptinit" << endl;
        return -1;
    }

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        cerr << "error evp_encryptupdate" << endl;
        return -1;
    }

    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        cerr << "error evp_encryptfinal" << endl;
        //return -1;
    }

    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int Encrypt::InternalDecrypt(unsigned char* ciphertext, int ciphertext_len, unsigned char* key,
    unsigned char* iv, unsigned char* plaintext)
{
    EVP_CIPHER_CTX* ctx;

    int len, plaintext_len;
    int errorCode = -1;

    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        cerr << "error getting cipher context" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    errorCode = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    if (1 != errorCode)
    {
        cerr << "error EVP_DecryptInit_ex, error code " << errorCode << endl;
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    errorCode = EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    if (1 != errorCode)
    {
        cerr << "error EVP_DecryptUpdate, error code " << errorCode << endl;
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    plaintext_len = len;

    errorCode = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    if (1 != errorCode)
    {
        cerr << "error EVP_DecryptFinal_ex, error code " << errorCode << endl;
        //EVP_CIPHER_CTX_free(ctx);
       // return -1;
    }

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}