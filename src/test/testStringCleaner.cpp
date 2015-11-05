//test StringCleaner

#include <iostream>
#include <string>
#include <fstream>
#include "StringCleaner.h"
using namespace std;

int main()
{
	ifstream fin("../../doc/XMLTest.txt");
	if(!fin)
		cout << "File Not Found" << endl;
	string text = "";
	string readMe;
	StringCleaner test;
	while(fin)
	{
		fin >> readMe;
		text += (test.clean(readMe) + " ");
	}
	stringstream stream(text);
	while(stream>>text)
		cout << text << " ";
	cout << endl;

	fin.close();
	return 0;
}
