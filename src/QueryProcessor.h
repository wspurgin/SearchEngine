/*
Nastasha Gerlt, Will Spurgin
Nov. 30, 2013
Data Structures - Search Engine
'QueryProccesor' header file

Duties of the Query Processor:
1. Accept queries - throw error if bad
2. Clean those queries
3. Pass words as keys to Index handler to search engine
4. once it retrieves a lis of docs for words in query, it will combine/edit those lists to match boolean statements
5. pass updated list to doc processor - which will return actual documents as strings to query processor
6. return list of docs (as strings) to UI
*/

#ifndef QueryProcessor_H
#define QueryProcessor_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Ranker.h"
#include "DocProcessor.h"
#include "StringCleaner.h"
#include "IndexHandler.h"

using namespace std;

class QueryProcessor
{
	private:
		string keywords[3];
		IndexHandler* handler;
		DocProcessor* processor;
		Ranker ranker;

	public:
		QueryProcessor();
		IndexHandler& getHandler();
		void setHandler(IndexHandler& handle);
		void setProcessor(DocProcessor& process);
		vector<string> query(string str);
		void cleanQuery(string& str);
		unordered_map<string,int> searchIndex(string word);
};
#endif
