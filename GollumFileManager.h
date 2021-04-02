
#pragma once
#include <vector>
#include <fstream>
#include <iostream>

#include "Models.h"
#include "Encryption/Encrypt.h"

using namespace std;

class GollumFileManager
{
public:
	vector<struct Credential> ReadFromFileStore();
	void WriteToFileStore(vector<struct Credential> credentials);
};