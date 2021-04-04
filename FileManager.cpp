
#include "FileManager.h"

vector<struct Credential> FileManager::ReadFromFileStore()
{
    ifstream fileStore("gollumstore", ios_base::binary);

    if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
    {
        std::cerr << "Error opening file store" << endl;
        return vector<struct Credential>();
    }

    string data;
    char ch;

    while (fileStore.get(ch))
    {
        data += ch;
    }

    fileStore.close();

    Encrypt* encryptor = new Encrypt();
    data = encryptor->DecryptString(data);

    vector<struct Credential> credentials;
    int credEnd = -1;
    string remainingData = data;

    do
    {
        struct Credential cred;

        credEnd = remainingData.find("</cred>");

        if (credEnd == -1)
            break;
        int passwordStart = remainingData.find("<p>");
        int nameEnd = remainingData.find("</n>");

        cred.Username = remainingData.substr(0, nameEnd);
        cred.Password = remainingData.substr(passwordStart + 3, credEnd - passwordStart -3 );

        credentials.push_back(cred);
        
        remainingData = remainingData.substr(credEnd + 7, data.size() - credEnd);
    } while (credEnd);

    return credentials;
}

void FileManager::WriteToFileStore(vector<struct Credential> credentials)
{
    Encrypt* encryptor = new Encrypt();
    
    fstream fileStore;
    fileStore.open("gollumstore", ios_base::out);

    if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
    {
        std::cerr << "Error opening file store" << endl;
        return;
    }

    string credentialsString = "";

    for (auto cred : credentials)
        credentialsString += cred.Serialize();

    string encryptedData = encryptor->EncryptString(credentialsString);

    fileStore << encryptedData;

    fileStore.close();
}