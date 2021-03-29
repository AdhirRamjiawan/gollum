
#include "AddAction.h"

using namespace std;

AddAction::AddAction()
{

}

AddAction::~AddAction()
{

}

void AddAction::DoAction()
{
    if (this->Argc != 6)
    {
        cout << GOLLUM_USAGE << endl;
        return;
    }

    Encrypt* encryptor = new Encrypt();
    ifstream inFileStore("gollumstore", ios_base::binary);
    bool inFileFailure = false;

    if ((inFileStore.rdstate() & std::ifstream::failbit) != 0)
    {
        cout << "Error opening file store. Attempting to recreate file store" << endl;
        inFileFailure = true;
    }

    string encryptedData, decryptedData;

    if (!inFileFailure)
    {
        char ch;
        while (inFileStore.get(ch))
        {
            encryptedData += ch;
        }
        decryptedData = encryptor->DecryptString(encryptedData);

        inFileStore.close();
    }

    fstream fileStore;
    fileStore.open("gollumstore", ios_base::out);

    if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
    {
        std::cerr << "Error opening file store" << endl;
        return;
    }

    string optionName = string(this->Argv[3]);
    string optionPassword = string(this->Argv[5]);
    string newCredential = optionName + "</n><p>" + optionPassword + "</cred>";

    encryptedData = encryptor->EncryptString(decryptedData + newCredential);

    fileStore << encryptedData;

    cout << "Ah! it's been added... my PRECIOUS!" << endl;

    fileStore.close();
}