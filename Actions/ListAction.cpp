
#include "ListAction.h"

using namespace std;

ListAction::ListAction()
{

}

ListAction::~ListAction()
{

}

void ListAction::DoAction()
{
    string output = "";
    Encrypt* encryptor = new Encrypt();
    ifstream fileStore("gollumstore", ios_base::binary);

    if ((fileStore.rdstate() & std::ifstream::failbit) != 0)
    {
        std::cerr << "Error opening file store" << endl;
        return;
    }

    cout << "What's in your pocketses?!" << endl;
    string data;
    vector<string> credentials;

    if (this->Argc == 3)
    {
        auto option1 = string(this->Argv[2]);

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
            cout << GOLLUM_USAGE << endl;
        }

        fileStore.close();
        return;
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