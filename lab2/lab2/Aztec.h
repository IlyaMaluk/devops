#ifndef AZTEC_H
#define AZTEC_H

#include <vector>
#include <string>

class Aztec
{

public:
	std::vector<std::string> aStrings;

	Aztec() {}
	virtual ~Aztec() {}

	void AddString(const char*);
	void ShowText();
};

#endif