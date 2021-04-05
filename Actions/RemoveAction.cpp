
#include "RemoveAction.h"

using namespace std;

RemoveAction::RemoveAction()
{

}

RemoveAction::~RemoveAction()
{

}

void RemoveAction::DoAction()
{
    if (this->Argc != 4)
    {
        cout << GOLLUM_USAGE << endl;
        return;
    }

    string name = this->Argv[3];
    auto credentials = fileManager->ReadFromFileStore();

    int index = 0;
    for (auto cred : credentials)
    {
        if (cred.Username == name)
            break;

        index++;
    }

    credentials.erase(credentials.begin() + index);

    fileManager->WriteToFileStore(credentials);

    cout << "Noooo... MY PRECIOUS!!!" << endl;
}