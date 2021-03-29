
#pragma once

#include <vector>
#include <string>

using namespace std;

class AbstractAction
{
public:
	virtual ~AbstractAction();
	void Setup(int argc, vector<string> argv);
	virtual void DoAction();
protected:
	int Argc;
	vector<string> Argv;
};