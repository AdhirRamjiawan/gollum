
#include "Encrypt.h"

#include <vector>


Encrypt::Encrypt()
{
}

string Encrypt::EncryptString(string plainText)
{
    struct AES_ctx ctx;
    uint8_t buffer[MAX_FILESTORE_SIZE_IN_CHARS] = { 0x0 };
    int paddingLength = plainText.size() % 16;

    // Padding using PCKS method: http://www.crypto-it.net/eng/theory/padding.html
    if (paddingLength != 0)
    {
        for (int i = 0; i < paddingLength; i++)
        {
            plainText += paddingLength;
        }
    }

    vector<uint8_t> myVector(plainText.begin(), plainText.end());

    for (int i = 0; i < plainText.size(); i++)
    {
        uint8_t c = myVector[i];
        buffer[i] = c;
    }

    AES_init_ctx_iv(&ctx, ENCRYPTION_KEY, ENCRYPTION_IV);

    AES_CBC_encrypt_buffer(&ctx, buffer, MAX_FILESTORE_SIZE_IN_CHARS);

    
    // convert buffer to string
    string encryptedText = "";
    
    for (auto ch : buffer)
        encryptedText += ch;

    return encryptedText;
}

string Encrypt::DecryptString(string encryptedText)
{
    struct AES_ctx dctx;
    uint8_t dbuffer[MAX_FILESTORE_SIZE_IN_CHARS] = { 0x0 };

    // copy encrypted data to decryption buffer
    for (int i = 0; i < MAX_FILESTORE_SIZE_IN_CHARS; i++)
    {
        if (encryptedText[i] == '\0')
            break;

        dbuffer[i] = encryptedText[i];
    }

    AES_init_ctx_iv(&dctx, ENCRYPTION_KEY, ENCRYPTION_IV);
    AES_CBC_decrypt_buffer(&dctx, dbuffer, MAX_FILESTORE_SIZE_IN_CHARS);

    // ############################################################ //
    // ##########  REMOVING PADDING AFTER DECRYPTION    ########### //
    // ############################################################ //

    uint8_t paddingChar = 0x0;
    int dataEndPos = -1;

    for (int i = 1; i < MAX_FILESTORE_SIZE_IN_CHARS; i++)
    {
        if (dbuffer[i] == 0x0)
        {
            paddingChar = dbuffer[i - 1]; /* loop must start from 1 to prevent -1 indexing */
            dataEndPos = i - 1;
            break;
        }
    }

    int paddingCount = 0;

    for (int i = dataEndPos; i > 0; i--)
    {
        if (dbuffer[i] == paddingChar)
            paddingCount++;
    }

    bool hasPadding = (paddingCount == (int)paddingChar);

    string decryptedText = "";

    if (hasPadding)
    {
        for (int i = 0; i < dataEndPos - paddingCount + 1; i++)
            decryptedText += (char)dbuffer[i];
    }


    return decryptedText;
}

