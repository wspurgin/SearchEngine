/*
Nastasha Gerlt, Will Spurgin
12/1/2013
Search Engine - Data Structures
'HashTableInterface' header file
*/

#ifndef HASH_TABLE_INTERFACE
#define HASH_TABLE_INTERFACE

#include "IndexInterface.h"
#include <stdexcept>
#include <sstream>

using namespace std;

class HashTableInterface : public IndexInterface
{
private:
    unordered_map<string, unordered_map<string, int> > index;

    void print(ostream& out) const;
public:
    HashTableInterface(string indexFilePath="index.txt");

    HashTableInterface(const HashTableInterface& rhs);

    ~HashTableInterface();

    void addWord(string word, string docID, int freq);

    void loadIndex();

    unordered_map<string, int> searchIndex(string word);

    void clearIndex();

    void writeIndex() const;

    void writeIndex(ostream& out) const;

    unordered_map<string, unordered_map<string, int> > getIndex() const;

    void setIndex(unordered_map<string, unordered_map<string, int> >& map);

    bool isIndexEmpty() const;
};

#endif
