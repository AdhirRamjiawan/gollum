
#pragma once
#include <string>
#include <iostream>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define MAX_FILESTORE_SIZE_IN_CHARS 100000

using namespace std;

class Encrypt
{
public:
	unsigned char* ENCRYPTION_KEY;
	unsigned char* ENCRYPTION_IV;
	Encrypt();
	string EncryptString(string plainText);
	string DecryptString(string encryptedText);
private:
	int InternalEncrypt(unsigned char* plaintext, int plaintext_len, unsigned char* key,
		unsigned char* iv, unsigned char* ciphertext);
	int InternalDecrypt(unsigned char* ciphertext, int ciphertext_len, unsigned char* key,
		unsigned char* iv, unsigned char* plaintext);
};