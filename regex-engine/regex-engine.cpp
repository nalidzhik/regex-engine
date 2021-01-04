#include <iostream>
#include <string>
#include <fstream>
#include "regex-engine.h"

using namespace std;

bool isLiteral(char ch)
{
	return isalnum(ch);
}

bool isStart(char ch)
{
	return ch == '^';
}

bool isDot(char ch)
{
	return ch == '.';
}

bool isPlus(char ch)
{
	return ch == '+';
}

bool isStar(char ch)
{
	return ch == '*';
}

bool isQuestion(char ch)
{
	return ch == '?';
}

bool isUnit(string term)
{
	return isLiteral(term[0]) || isDot(term[0]);
}

bool doesUnitMatch(string& regex, string& input)
{
	if (input.size() == 0)
	{
		return false;
	 }

	if (isLiteral(regex[0]))
	{
		return regex[0] == input[0];
	}
	else if (isDot(regex[0]))
	{
		return true;
	}
	
	return false;
}

bool matchRegex(string& regex, string& input)
{
	if (regex.size() == 0)
	{
		return true;
	}

	if (isUnit(regex))
	{
		if (doesUnitMatch(regex, input))
		{
			string regexRest = regex.substr(1);
			string inputRest = input.substr(1);
			return matchRegex(regexRest, inputRest);
		}
	}

	return false;
}

bool match(string& regex, string& input)
{
	int matchPos = 0;
	bool matched = false;

	int maxMatchPos;
	if (isStart(regex[0]))
	{
		maxMatchPos=0;
		regex=regex.substr(1);
	}
	else
	{
		maxMatchPos = input.size() - 1;
	}

	while (!matched && matchPos <= maxMatchPos)
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
