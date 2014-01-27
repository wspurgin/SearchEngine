/*
Nastasha Gerlt, Will Spurgin
11/16/2013
Data Structures - Search Engine
'DocLoader' header file
*/

#ifndef DOC_LOADER_H
#define DOC_LOADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sys/stat.h>
#include <stdexcept>

#include "rapidxml_utils.hpp"

using namespace std;

class DocLoader
{
private:
	unordered_map<string, string> file_structure;

public:
	//Default Constructors
	DocLoader();

	//Copy Constructor
	DocLoader(const DocLoader& rhs);

	//Destructor
	~DocLoader();

	unordered_map<string, string> getFileStructure() const;

	void addIdPathPair(string id, string path);

	vector<string> loadDocument(string id);

	void loadFileStructure();

	void writeFileStructure();

	void clearFileStructure();

	//overloaded operators
	DocLoader& operator=(const DocLoader& rhs);
};

#endif
