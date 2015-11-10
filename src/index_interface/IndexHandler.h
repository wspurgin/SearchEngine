/*
Nastasha Gerlt, Will Spurgin
12/1/2013
Search Engine - Data Structures
'IndexHandler' header file
*/

#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

#include "IndexInterface.h"
#include "AVLInterface.h"
#include "HashTableInterface.h"

using namespace std;

class IndexHandler
{
private:
    IndexInterface* interface;

public:
    IndexHandler(bool buildAVL=false, string indexFilePath="index.txt");

    IndexHandler(const IndexHandler& rhs);

    ~IndexHandler();

    bool setUpIndex(bool asAVL=false);

    unordered_map<string, int> searchIndex(string word);

    void addWord(string word, string docID, int freq);

    void clearIndex();

    IndexInterface* getInterface() const;

    void setInterface(IndexInterface* interface);

};

#endif
