/*
Nastasha Gerlt, Will Spurgin
11/18/2013
Data Structures - Search Engine
'IndexWord' class
*/

#ifndef INDEX_WORD_H
#define INDEX_WORD_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class IndexWord
{
public:
	string word;
	unordered_map<string, int> rankingPairs;
	IndexWord()
	{
		this->word = "";
	}
	
	IndexWord(string str)
	{
		this->word = str;
	}

	IndexWord(const IndexWord& rhs)
	{
		this->word = rhs.word;
		this->rankingPairs = rhs.rankingPairs;
	}

	IndexWord& operator=(const IndexWord& rhs)
	{
		this->word = rhs.word;
		this->rankingPairs = rhs.rankingPairs;
		return *this;
	}

	//Overloaded operators (only comparisions shoule be on the string 'word')

	bool operator==(const IndexWord& rhs) const
	{ return (this->word == rhs.word); }

	bool operator!=(const IndexWord& rhs) const
	{ return !(*this == rhs); }

	bool operator<(const IndexWord& rhs) const
	{ return (this->word < rhs.word); }

	bool operator>(const IndexWord& rhs) const
	{ return !(*this < rhs); }

	bool operator<=(const IndexWord& rhs) const
	{ return (*this < rhs || *this == rhs); }

	bool operator>=(const IndexWord& rhs) const
	{ return (*this > rhs || *this == rhs); }

	IndexWord& operator+=(const IndexWord& rhs)
	{
		for(auto& x: rhs.rankingPairs)
			this->rankingPairs.insert(x);
		return *this;
	}

	friend ostream& operator<<(ostream& out, const IndexWord& rhs)
	{
		out << rhs.word << " ";
		for(auto& x: rhs.rankingPairs)
			out << x.first << " " << x.second << " ";
		return out;
	}
};

#endif
