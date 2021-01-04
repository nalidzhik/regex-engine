#include <iostream>
#include <string>
#include <fstream>
#include "regex-engine.h"

using namespace std;

int main()
{
	string regex = "a.c.";
	string input = "abc";

	cout << match(regex, input) << endl;

	return 0;
}
