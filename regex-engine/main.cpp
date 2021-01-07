#include <iostream>
#include <string>
#include <fstream>
#include "regex-engine.h"

using namespace std;

int main()
{
	string regex = "c?ba";
	string input = "cba";

	cout << match(regex, input) << endl;

	return 0;
}
