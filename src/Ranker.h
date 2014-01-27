/*
Nastasha Gerlt, Will Spurgin
Dec. 4, 2013
Data Structures - Search Engine
'Ranker' header file
*/

#ifndef RANKER_H
#define RANKER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Ranker
{
	private:
		unordered_map<string, unordered_map<string, int> > bigList;

	public:
		Ranker();
		void addList(unordered_map<string,int> map, string keyword);
        vector<string> rank();
		int getTotalFreq(unordered_map<string, int>& map);
        bool isEmpty();
        unordered_map<string,int> mergeLists(unordered_map<string,int> list1, unordered_map<string,int> list2);
        unordered_map<string,int> removeStuff(unordered_map<string,int> yesList, unordered_map<string,int> notList);
        unordered_map<string,int> combineLists(unordered_map<string,int> list1, unordered_map<string,int> list2);
};
#endif
