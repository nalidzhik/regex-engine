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
* <main file>
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include "regex-engine.h"

using namespace std;

int strlen(string& regex);
bool isSpecialSymbol(char ch);
bool isCorrectRegex(string& regex);
bool hasMoreSpecialSymbols(string& regex);

int main()
{
	string regex;
	cin >> regex;
	bool validate = isCorrectRegex(regex);
	bool validateSymbols = hasMoreSpecialSymbols(regex);

	if (!validate || !validateSymbols)
	{
		cout << "Error in input regex" << endl;
	}

	string filepath;
	cin >> filepath;
	fstream text(filepath, fstream::in);

	char* line = new char[150];

	if (!text.is_open())
	{
		cout << "Could not open the file!" << endl;
	}
	else
	{
		text.seekp(0);

		while (text.get(line, 150, '\n'))
		{
			text.ignore(875, '\n');
			string lineAsString(line);
			if (match(regex, lineAsString))
			{
				cout << lineAsString;
				cout << endl;
			}

			text.clear();
		}
		text.close();

	}
	delete[] line;

	return 0;
}

int strlen(string& regex)
{
	int counter = 0;
	while (regex[counter] != '\0')
	{
		++counter;
	}
	return counter;
}

bool isSpecialSymbol(char ch)
{
	return ch == '.' || ch == '*' || ch == '+' || ch == '?';
}

bool isCorrectRegex(string& regex)
{
	for (int i = 0;i < strlen(regex) - 1;i++)
	{
		if (regex[i] == regex[i + 1] && isSpecialSymbol(regex[i]))
		{

			return false;
		}
	}

	return true;
}

bool hasMoreSpecialSymbols(string& regex)
{
	int countSpecialSymbols = 0;
	for (int i = 0; i < strlen(regex);i++)
	{
		if (regex[i] == '*' || regex[i] == '+' || regex[i] == '?')
		{
			++countSpecialSymbols;
		}
	}
	if (countSpecialSymbols >= 2)
	{
		return false;
	}

	return true;
}