
#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "../GollumStrings.h"
#include "../Encryption/Encrypt.h"
#include "../AbstractAction.h"
#include "../Models.h"
#include "../FileManager.h"

using namespace std;

class ListAction : public AbstractAction
{
public:
	ListAction();
	~ListAction();
	void DoAction();
};