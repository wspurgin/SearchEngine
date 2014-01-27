/*
Nastasha Gerlt, Will Spurgin
11/19/2013
Data Structures - Search Engine
'IndexInterface' header file
*/

#ifndef INDEX_INTERFACE
#define INDEX_INTERFACE

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class IndexInterface
{
protected:

    string indexFilePath;

public:
    
    IndexInterface() { indexFilePath="../index.txt"; }

    virtual ~IndexInterface() {};

    virtual void addWord(string word, string docID, int freq) = 0;

    virtual void loadIndex() = 0;

    virtual unordered_map<string, int> searchIndex(string word) = 0;

    virtual void clearIndex() = 0;

    virtual void writeIndex() const = 0;

    virtual void writeIndex(ostream& out) const = 0;

    string getIndexFilePath() const { return this->indexFilePath; }

    void setIndexFilePath(string path) { this->indexFilePath = path; }
};

#endif
