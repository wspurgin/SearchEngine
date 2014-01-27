/*
Nastasha Gerlt, Will Spurgin
Nov. 20, 2013
Data Structures - Search Engine
'StringCleaner' header file
*/

#ifndef STRINGCLEANER_H
#define STRINGCLEANER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "AVLTree.hpp"
using namespace std;

class StringCleaner
{
	private:
		AVLTree<string> stopList;

	public:
		StringCleaner();
		string clean(const string& dirty);;
		string removeStopWords(stringstream& cleanMe);
		void stemWord(string& cleanMe);
		bool isPunc(char c);
		bool isStopWord(string& cleanMe);
};
#endif
