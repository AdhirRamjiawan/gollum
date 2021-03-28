// Gollum.cpp : Defines the entry point for the application.
//

//#define GOLLUM_DEBUG

#include <fstream>
#include "Gollum.h"
#include "Encrypt.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Gollum v1.0.0" << endl;

    string usage = R"(
    usage: gollum <action> <options>
    actions:
        - list      (lists all credentials from store. Options: [--show-pass, --pattern])
        - add       (add a new credential to store. Options: [--name, --password])
        - remove    (remove a credential from store. Options: [--name])
        - help      (displays this message)
    )";

    if (argc < 1)
    {
        cout << usage << endl;
        return 0;
    }

    auto action = string(argv[1]);

#ifdef  GOLLUM_DEBUG
    cout << "argument count : " << argc << endl;

    for (int i = 0; i < argc; i++)
    {
        cout << "arg [" << i << "]: " << argv[i] << endl;
    }

    cout << "action : " << action << endl;
#endif //  GOLLUM_DEBUG

    if (action == "list")
    {
        Encrypt *encryptor = new Encrypt();
        ifstream fileStore("gollumstore");
        if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
        {
            std::cerr << "Error opening file store" << endl;
            return 0;
        }

        string data;
        cout << "What's in your pocketses?!" << endl;

        if (argc == 3)
        {
            auto option1 = string(argv[2]);

            if (option1 == "--show-pass")
            {
                fileStore >> data;
            }
            else
            {
                cout << usage << endl;
            }

            fileStore.close();
            return 0;
        }
        else
        {
            fileStore >> data;
        }
        
        data = encryptor->DecryptString(data);

        cout << data << endl;
        fileStore.close();
    }
    else if (action == "add")
    {
        if (argc != 6)
        {
            cout << usage << endl;
            return 0;
        }

        Encrypt* encryptor = new Encrypt();
        ifstream inFileStore("gollumstore");
        bool inFileFailure = false;

        if ((inFileStore.rdstate() & std::ifstream::failbit) != 0)
        {
            cout << "Error opening file store. Attempting to recreate file store" << endl;
            inFileFailure = true;
        }
        
        string encryptedData, decryptedData;
        
        if (!inFileFailure)
        {
            inFileStore >> encryptedData;
            decryptedData = encryptor->DecryptString(encryptedData);

            inFileStore.close();
        }

        fstream fileStore;
        fileStore.open("gollumstore", ios_base::out);

        if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
        {
            std::cerr << "Error opening file store" << endl;
            return 0;
        }

        string optionName = string(argv[3]);
        string optionPassword = string(argv[5]);
        string newCredential = optionName + "</n><p>" + optionPassword;
        
        encryptedData = encryptor->EncryptString(decryptedData + "\n" + newCredential);

        fileStore << encryptedData << endl;

        cout << "Ah! it's been added... my PRECIOUS!" << endl;

        fileStore.close();
    }
    else if (action == "remove")
    {

    }

    
    return 0;
}