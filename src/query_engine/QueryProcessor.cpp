/*
Nastasha Gerlt, Will Spurgin
Nov. 30, 2013
Data Structures - Search Engine
'QueryProccesor' class file

Duties of the Query Processor:
1. Accept queries - throw error if bad
2. Clean those queries
3. Pass words as keys to Index handler to search engine
4. once it retrieves a lis of docs for words in query, it will combine/edit those lists to match boolean statements
5. pass updated list to doc processor - which will return actual documents as strings to query processor
6. return list of docs (as strings) to UI
*/

#include "QueryProcessor.h"

using namespace std;


QueryProcessor::QueryProcessor()
{
	keywords[0] = "NOT"; keywords[1] = "AND"; keywords[2] = "OR";
	handler = NULL;
	processor = NULL;
}

IndexHandler& QueryProcessor::getHandler()
{
	return *handler;
}

void QueryProcessor::setHandler(IndexHandler& handle)
{
	handler = &handle;
}

void QueryProcessor::setProcessor(DocProcessor& process)
{
	this->processor = &process;
}

vector<string> QueryProcessor::query(string str)
{

	//gets the search input
	stringstream stream(str);
	vector<string> searchWords;
	string temp;
	while(stream.good())
	{
		stream >> temp;
		if(temp == "")
			break;
		searchWords.push_back(temp);
		temp = "";
	}

	//find words to search for and add them to a list of current documents
	
	string currentKeyword = "";
	unordered_map<string,int> currDocs;

	for(int i = 0; i < searchWords.size(); i++)
	{
		bool isKeyword = false;
		for(int j = 0; j < 3; j++)
		{
			if(searchWords[i] == keywords[j])
			{
				isKeyword = true;
				currentKeyword = keywords[j];
			}
		}
		if(isKeyword == false)
		{
			int type = -1;
			if(currentKeyword == "AND")
				type = 0;
			else if(currentKeyword == "OR")
				type = 1;
			else if(currentKeyword == "NOT")
				type = 2;

			switch(type)
			{
				case 0:
					this->ranker.addList(searchIndex(searchWords[i]), "AND");
					break;
				case 1:
					this->ranker.addList(searchIndex(searchWords[i]), "OR");
					break;
				case 2:
					if(this->ranker.isEmpty())
					{
						this->ranker.addList(this->processor->getAllFilesInIndex(), "NONE");
						this->ranker.addList(searchIndex(searchWords[i]), "NOT");
					}
					else
						this->ranker.addList(searchIndex(searchWords[i]), "NOT");
					break;
				default:
						this->ranker.addList(searchIndex(searchWords[i]), "NONE");
					break;	
			}
		}

		
	}

	// sort and return top 15 docs
	return this->ranker.rank();
}

void QueryProcessor::cleanQuery(string& str)
{
	stringstream sin(str);
	str = "";
	string me;
	StringCleaner please;
	bool isKeyword = false;
	while(sin >> me)
	{
		for(int i = 0; i < 3; i++)
		{
			if(keywords[i] == me)
				isKeyword = true;
		}
		if(!isKeyword)
			please.clean(me);
		str += me;
	}
}

unordered_map<string,int> QueryProcessor::searchIndex(string word)
{
	//brings in search word, returns complete list of doc/freq pairs
	return this->handler->searchIndex(word);
}
