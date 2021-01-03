#include <iostream>
#include <string>
#include <fstream>
#include "regex-engine.h"

using namespace std;

bool doesUnitMatch(string& regex, string& input)
{
	return regex[0] == input[0];
}

bool matchRegex(string& regex, string& input)
{
	if (regex.size() == 0)
	{
		return true;
	}

	if (doesUnitMatch(regex, input))
	{
		string regexRest = regex.substr(1);
		string inputRest = input.substr(1);
		return matchRegex(regexRest, inputRest);
	}

	return false;
}

bool match(string& regex, string& input)
{
	int matchPos = 0;
	bool matched = false;
	while (!matched && matchPos < input.size())
	{
		string inputRest = input.substr(matchPos);
		matched = matchRegex(regex, inputRest);
		if (matched)
		{
			return true;
		}

		matchPos += 1;
	}

	return false;
}
