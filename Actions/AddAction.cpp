
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

    struct Credential newCred;
    newCred.Username = string(this->Argv[3]);
    newCred.Password = string(this->Argv[5]);
    
    auto credentials = fileManager->ReadFromFileStore();
    credentials.push_back(newCred);

    fileManager->WriteToFileStore(credentials);

    cout << "Credential added to file... MY PRECIOUS!!!" << endl;
}