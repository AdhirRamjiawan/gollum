
#pragma once

#include <string>

using namespace std;

struct Credential {
	string Username;
	string Password;
	string Serialize();
};

inline string Credential::Serialize()
{
	return this->Username + "</n><p>" + this->Password + "</cred>";
}