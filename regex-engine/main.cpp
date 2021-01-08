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

int main()
{
	string regex;
	cin >> regex;

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
