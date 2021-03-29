
#include "AbstractAction.h"

AbstractAction::~AbstractAction()
{

}

void AbstractAction::Setup(int argc, vector<string> argv)
{
	this->Argv = argv;
	this->Argc = argc;
}

void AbstractAction::DoAction()
{

}