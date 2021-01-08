/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Nazife Alidzhik
* @idnumber 62598
* @compiler VC
*
* <file with all functions>
*
*/

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

bool isOperator(char ch)
{
	return isStar(ch) || isPlus(ch) || isQuestion(ch);
}

bool isDot(char ch)
{
	return ch == '.';
}

bool isEscape(char ch)
{
	return ch == '\\';
}

bool isEscapeSequence(char term)
{
	return isEscape(term);
}

bool isUnit(string term)
{
	return isLiteral(term[0]) || isDot(term[0]);
}

struct splitResult
{
	char head;
	char oper;
	string rest;
};

splitResult splitRegex(string& regex)
{
	int lastRegexPos = 0;
	char oper = '\0';
	splitResult result;

	if (isEscape(regex[0]))
	{
		lastRegexPos += 2;
		char head = regex[2];

		result.head = head;
	}
	else
	{
		lastRegexPos = 1;
		char head = regex[0];

		result.head = head;
	}

	if (lastRegexPos < regex.size() && isOperator(regex[lastRegexPos]))
	{
		oper = regex[lastRegexPos];
		lastRegexPos += 1;

	}
	string rest = regex.substr(lastRegexPos);

	result.oper = oper;
	result.rest = rest;


	return result;
}

bool doesUnitMatch(string& regex, string& input)
{
	splitResult result = splitRegex(regex);

	char head = result.head;
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
	else if (isEscapeSequence(head))
	{
		return false;
	}

	return false;
}



bool matchMultiple(string& regex, string& input, int minMatchLength, int maxMatchLength)
{
	splitResult result = splitRegex(regex);

	if (minMatchLength < 0)
	{
		minMatchLength = 0;
	}

	int submatchLength = -1;

	while (maxMatchLength == -1 || submatchLength < maxMatchLength)
	{
		string newRegex = string(submatchLength + 1, result.head);
		bool subexprMatched = matchRegex(newRegex, input);

		if (subexprMatched)
		{
			submatchLength += 1;
		}
		else
		{
			break;
		}
	}

	while (submatchLength >= minMatchLength)
	{
		string newRegex = string(submatchLength, result.head) + result.rest;
		bool matched = matchRegex(newRegex, input);
		if (matched)
		{
			return matched;
		}

		submatchLength -= 1;
	}

	return false;
}

bool matchStar(string& regex, string& input)
{
	return matchMultiple(regex, input, -1, -1);
}

bool matchPlus(string& regex, string& input)
{
	return matchMultiple(regex, input, 1, -1);
}

bool matchQuestion(string& regex, string& input)
{
	return matchMultiple(regex, input, 0, 1);
}

bool matchRegex(string& regex, string& input)
{
	if (regex.size() == 0)
	{
		return true;
	}

	splitResult result = splitRegex(regex);

	if (isStar(result.oper))
	{
		return matchStar(regex, input);
	}
	else if (isPlus(result.oper))
	{
		return matchPlus(regex, input);
	}
	else if (isQuestion(result.oper))
	{
		return matchQuestion(regex, input);
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
		maxMatchPos = 0;
		regex = regex.substr(1);
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
