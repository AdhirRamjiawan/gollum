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
        string output = "";
        Encrypt *encryptor = new Encrypt();
        ifstream fileStore("gollumstore", ios_base::binary);

        if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
        {
            std::cerr << "Error opening file store" << endl;
            return 0;
        }

        cout << "What's in your pocketses?!" << endl;
        string data;
        vector<string> credentials;

        if (argc == 3)
        {
            auto option1 = string(argv[2]);

            if (option1 == "--show-pass")
            {
                char ch;
                while (fileStore.get(ch))
                {
                    data += ch;
                }
                output = encryptor->DecryptString(data);
                cout << output << endl;
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
            string tmp = "";

            char ch;
            while (fileStore.get(ch))
            {
                data += ch;
            }

            data = encryptor->DecryptString(data);

            int part = -1;
            int lastIndex = -1;
            string remainingData = data;

            do
            {
                part = remainingData.find("</n>");
                output = remainingData.substr(lastIndex + 1, part);
                remainingData = remainingData.substr(part, data.size() - part);
                lastIndex = part;
                credentials.push_back(output);
            } while (part);
        }

        for (auto cred : credentials)
        {
            cout << cred << endl;
        }
        
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
            return 0;
        }

        string optionName = string(argv[3]);
        string optionPassword = string(argv[5]);
        string newCredential = optionName + "</n><p>" + optionPassword + "</cred>";
        
        encryptedData = encryptor->EncryptString(decryptedData + newCredential);

        fileStore << encryptedData;

        cout << "Ah! it's been added... my PRECIOUS!" << endl;

        fileStore.close();
    }
    else if (action == "remove")
    {

    }

    
    return 0;
}