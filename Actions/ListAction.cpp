
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
    cout << "What's in your pocketses?!" << endl;
    vector<struct Credential> credentials = fileManager->ReadFromFileStore();

    if (this->Argc == 3)
    {
        auto option1 = string(this->Argv[2]);

        if (option1 == "--show-pass")
        {
            for (auto cred : credentials)
                cout << cred.Username << " " << cred.Password << endl;
        }
        else
        {
            cout << GOLLUM_USAGE << endl;
        }

        return;
    }
    else
    {
        for (auto cred : credentials)
            cout << cred.Username << endl;
    }
}