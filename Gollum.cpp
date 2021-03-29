// Gollum.cpp : Defines the entry point for the application.
//

//#define GOLLUM_DEBUG

#include <fstream>
#include "Gollum.h"
#include "Encrypt.h"
#include "AbstractAction.h"
#include "Actions/ListAction.h"
#include "Actions/AddAction.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Gollum v1.0.0" << endl;

    if (argc < 1)
    {
        cout << GOLLUM_USAGE << endl;
        return 0;
    }

    auto action = string(argv[1]);

    AbstractAction *actionType = new ListAction();
    vector<string> arguments(argv, argv + argc);

    if (action == "list")
    {
        actionType = new ListAction();
        actionType->Setup(argc, arguments);
    }
    else if (action == "add")
    {
        actionType = new AddAction();
        actionType->Setup(argc, arguments);
    }
    else if (action == "remove")
    {

    }
    else
    {
        cout << GOLLUM_USAGE << endl;
        return 0;
    }

    actionType->DoAction();

    
    return 0;
}