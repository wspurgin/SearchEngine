/*
Nastasha Gerlt, Will Spurgin
Dec. 5, 2013
Data Structures - Search Engine
'Ranker' class file
*/

#include "Ranker.h"

using namespace std;

Ranker::Ranker()
{
 // Yay it's constructed!
}

vector<string> Ranker::rank()
{
	//brings in a list of string ids and freq in a map and wants to rank them by the freq of word passed in
	vector<string> topFifteen;
	unordered_map<string, int> map;

	if(!this->bigList["NONE"].empty()) // NONE is not empty
		map = this->bigList["NONE"];
	else if(!this->bigList["AND"].empty() && !this->bigList["OR"].empty()) // both AND and OR are not empty
		map = combineLists(this->bigList["AND"], this->bigList["OR"]);
	else if(!this->bigList["OR"].empty()) //  AND is empty(because of previous statement failing) and OR is not empty
		map = this->bigList["OR"];
	else // AND is not empty and OR is empty
		map = this->bigList["AND"];

	//Take out anything in the NOT list if NOT list is not empty
	if(!this->bigList["NOT"].empty())
		map = removeStuff(map, this->bigList["NOT"]);

	int length = 15;
	if(map.size() < 15)
		length = map.size();
	
	for(int k = 0; k < length; k++)
	{
		unordered_map<string, int>::iterator highest = map.begin();
		for(unordered_map<string, int>::iterator j = ++map.begin(); j != map.end(); ++j)
		{
			if(highest->second < j->second)
			{
				highest = j;
			}
		}
		//pushs the document id, plus the tf/idf for that doc.
		stringstream s;
		s << highest->first << " " << highest->second;
		topFifteen.push_back(s.str());
		map.erase(highest);
	}

	this->bigList.clear();
	return topFifteen;
}

void Ranker::addList(unordered_map<string,int> map, string keyword)
{
	if(keyword == "NOT")
	{
		for(auto& x : map)
			this->bigList[keyword][x.first] = x.second;
	}
	else if(keyword == "AND" || keyword == "OR")
	{
		int corpusFreq = getTotalFreq(map);
		bool listWasEmpty = false;
		bool combine = false;
		for(auto& x : map)
			x.second = 100*((double)x.second / (double)corpusFreq);
		
		if(keyword == "AND")
		{
			if(!this->bigList[keyword].empty())
				listWasEmpty = true;
			else
				combine = false;
		}
		else if(keyword == "OR")
		{
			if(!this->bigList[keyword].empty())
				listWasEmpty = true;
			else
				combine = true;
		}

		if(!listWasEmpty)
			this->bigList[keyword] = map;
		else if(combine)
			this->bigList[keyword] = combineLists(this->bigList[keyword], map);
		else
			this->bigList[keyword] = mergeLists(this->bigList[keyword], map);
	}
	else
		this->bigList["NONE"] = map;
}

int Ranker::getTotalFreq(unordered_map<string,int>& map)
{
	//return the total freq of a word in entire index
	int wordTotal = 0;

	for(auto& x : map)
	{
		wordTotal += x.second;
	}

	return wordTotal;
	
}

bool Ranker::isEmpty()
{
	return this->bigList.empty();
}

unordered_map<string,int> Ranker::mergeLists(unordered_map<string,int> list1, unordered_map<string,int> list2)
{
	//return a doc/freq list with only the pairs that appear in both lists
	//remember to adjust frequencies
	auto it2 = list2.begin();
	bool areSame;
	unordered_map <string,int> map;
	for(auto& x: list1)
	{
		it2 = list2.begin();
		areSame = false;
		while(it2 != list2.end())
		{
			if(x.first == (*it2).first)
			{
				areSame = true;
				x.second += (*it2).second;
				break;
			}
			++it2;
		}
		if(areSame == true)
			map.insert(x);
	}
	return map;
}

unordered_map<string,int> Ranker::removeStuff(unordered_map<string,int> yesList, unordered_map<string,int> notList)
{
	//take out all the pairs that are also found in the not list.
	auto it2 = notList.begin();
	bool areSame;
	unordered_map <string,int> map;
	for(auto& x: yesList)
	{
		it2 = notList.begin();
		areSame = false;
		while(it2 != notList.end())
		{
			if(x.first == (*it2).first)
			{
				areSame = true;
				break;
			}
			++it2;
		}
		if(areSame != true)
			map.insert(x);
	}
	return map;
}

unordered_map<string,int> Ranker::combineLists(unordered_map<string,int> list1, unordered_map<string,int> list2)
{
	//return a doc/freq list with the pairs that appear in both lists, take out duplicates
	//remember to adjust frequencies
	auto it2 = list2.begin();
	bool areSame;
	for(auto& x: list1)
	{
		it2 = list2.begin();
		areSame = false;
		while(it2 != list2.end())
		{
			if(x.first == (*it2).first)
			{
				areSame = true;
				(*it2).second += x.second;
				break;
			}
			++it2;
		}
		if(areSame != true)
			list2.insert(x);
	}

	return list2;
}

