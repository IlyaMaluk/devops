#include "Aztec.h"

// Working function that adds string to an array
void Aztec::AddString(const char* str)
{
	aStrings.push_back(str);
}

void Aztec::ShowText()
{
	for (auto &str : aStrings)
	{
		printf("%s\n", str.c_str());
	}
}
