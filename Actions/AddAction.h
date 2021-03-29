
#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "../GollumStrings.h"
#include "../Encrypt.h"
#include "../AbstractAction.h"

using namespace std;

class AddAction : public AbstractAction
{
public:
	AddAction();
	virtual ~AddAction();
	void DoAction();
};