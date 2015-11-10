/*
Nastasha Gerlt, Will Spurgin
12/1/2013
Search Engine - Data Structures
'IndexHandler' implentation file
*/

#include "IndexHandler.h"

IndexHandler::IndexHandler(bool buildAVL, string indexFilePath)
{
    if(!buildAVL)
    {
        cout << "Building Index as Hash Table" << endl;
        this->interface = new HashTableInterface(indexFilePath);
    }
    else
    {
        cout << "Building Index as AVL tree" << endl;
        this->interface = new AVLInterface();
    }
}

IndexHandler::IndexHandler(const IndexHandler& rhs)
{
    //WARNING: copying IndexHandlers is a bad Idea! We don't want
    // multiples of the same index floating around. So data integrity
    // isn't garaunteed.
    this->interface = rhs.getInterface();
}

IndexHandler::~IndexHandler()
{
  cout << "Wrting out Index...";
  this->interface->writeIndex();
  cout << "    Done" << endl;
  delete this->interface;
}

bool IndexHandler::setUpIndex(bool asAVL)
{
    //write out current index regardless of type and free 'interface'
    try
    {
        this->interface->writeIndex();
        delete this->interface;
    }
    catch(exception& e)
    {
        return false;
    }
    if(!asAVL)
        this->interface = new HashTableInterface();
    else
        this->interface = new AVLInterface();
    //index has been successfully rebuilt
    return true;
}

unordered_map<string, int> IndexHandler::searchIndex(string word)
{
    return this->interface->searchIndex(word);
}

void IndexHandler::addWord(string word, string docID, int freq)
{
    this->interface->addWord(word, docID, freq);
}

void IndexHandler::clearIndex()
{
    this->interface->clearIndex();
}
IndexInterface* IndexHandler::getInterface() const
{
    return this->interface;
}

void IndexHandler::setInterface(IndexInterface* interface)
{
    this->interface = interface;
}
