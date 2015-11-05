/*
Nastasha Gerlt, Will Spurgin
Nov. 20, 2013
Data Structures - Search Engine
'StringCleaner' class file
*/

#include "StringCleaner.h"

using namespace std;


StringCleaner::StringCleaner()
{

	//load stopwords
	ifstream fin("../doc/StopWords.txt");
	string stopword;

	while(fin>>stopword)
		stopList.insert(stopword);

}

string StringCleaner::clean(const string& dirty)
{
	//cleans initial dirty string
	stringstream cleaner;
	for(int i = 0; i < dirty.length(); i++)
	{
		char temp = dirty[i];
		//isPunc includes non ascii chars
		if(isPunc(temp))
		{
			cleaner << " ";
			continue;
		}
		temp = tolower(temp);
		cleaner << temp;
	}
	return removeStopWords(cleaner);
}

string StringCleaner::removeStopWords(stringstream& cleanMe)
{
	//gets rid of stop words
	string temp;
	string cleaned;
	while(cleanMe>>temp)
	{
		if(isStopWord(temp) == false)
			cleaned += temp + " ";
		else
			cleaned += "";		
	}
	return cleaned;

}

bool StringCleaner::isPunc(char c)
{
	//determines if character is a punctuation mark or non ascii character
	int value = c;
	if( (value >= 65 && value <= 90) || (value >= 97 && value <= 122) )
		return false;
	else
		return true;
}

bool StringCleaner::isStopWord(string& cleanMe)
{
	//Check if stop word
	return stopList.isFound(cleanMe);
}



