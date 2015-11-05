/*
Nastasha Gerlt, Will Spurgin
11/16/2013
Data Structures - Search Engine
'DocProcessor' header file
*/

#ifndef DOC_PROCESSOR_H
#define DOC_PROCESSOR_H

//inclusions
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <unordered_map>
#include <vector>

#include "StringCleaner.h"
#include "DocLoader.h"
#include "IndexHandler.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;

class DocProcessor
{
private:
	int blockSize;
	bool fileStructureBuilt;
	DocLoader loader;
	StringCleaner cleaner;
	IndexHandler* handler;

public:
	//Default Constructors
	DocProcessor();

	DocProcessor(int size);

	//Copy Constructor
	DocProcessor(const DocProcessor& rhs);

	//Destructor
	~DocProcessor();

	int getBlockSize() const;

	bool isFileStructureBuilt() const;

	unordered_map<string, int> getAllFilesInIndex() const;

	DocLoader getLoader() const;

	StringCleaner getCleaner() const;

	IndexHandler& getHandler() const;

	void setBlockSize(int size);

	void setFileStructureBuilt(bool isBuilt);

	void setLoader(const DocLoader& l);

	void setCleaner(const StringCleaner& c);

	void setHandler(IndexHandler& h);

	//calls Document loader to load document
	vector<string> load(string docID);

	void readDocs(const char* filePath);

	void buildFileStructure();

	void clearFileStructure();

	//overloaded assingment operator
	DocProcessor& operator=(const DocProcessor& rhs);
};

#endif
