
#pragma once

#include "../AbstractAction.h"
#include "../GollumStrings.h"

class RemoveAction : public AbstractAction
{
public:
	RemoveAction();
	~RemoveAction();
	void DoAction();
};