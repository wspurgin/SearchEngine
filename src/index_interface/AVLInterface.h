/*
Nastasha Gerlt, Will Spurgin
11/24/2013
Search Engine - Data Structures
'AVLInterface' header file
*/

#ifndef AVL_INTERFACE_H
#define AVL_INTERFACE_H

#include "IndexInterface.h"
#include "AVLInterface.h"
#include "AVLTree.hpp"
#include "IndexWord.h"
#include <stdexcept>
#include <sstream>

using namespace std;

class AVLInterface : public IndexInterface
{
private:
    AVLTree<IndexWord> index;

public:
    AVLInterface();

    ~AVLInterface();

    AVLInterface(const AVLInterface& rhs);

    void addWord(string word, string docID, int freq);

    void loadIndex();

    unordered_map<string, int> searchIndex(string word);

    void clearIndex();

    void writeIndex() const;

    void writeIndex(ostream& out) const;
};

#endif
