
#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "../GollumStrings.h"
#include "../Encrypt.h"
#include "../AbstractAction.h"

using namespace std;

class ListAction : public AbstractAction
{
public:
	ListAction();
	~ListAction();
	void DoAction();
};