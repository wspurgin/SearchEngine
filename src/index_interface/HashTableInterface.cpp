/*
Nastasha Gerlt, Will Spurgin
12/1/2013
Search Engine - Data Structures
'HashTableInterface' implementation file
*/

#include "HashTableInterface.h"

using namespace std;

HashTableInterface::HashTableInterface(string indexFilePath) : IndexInterface(indexFilePath)
{
  loadIndex();
}

HashTableInterface::HashTableInterface(const HashTableInterface& rhs)
{
    this->index = rhs.getIndex();
}

HashTableInterface::~HashTableInterface()
{
    //write out index
    writeIndex();

    //nothing else to do, the unordered_map takes care of itself
}

void HashTableInterface::print(ostream& out) const
{
    for(auto& x: this->index)
    {
        out << x.first << " ";
        for(auto& i: x.second)
            out << i.first << " " << i.second << " ";
        out << endl;
    }
}

void HashTableInterface::addWord(string word, string docID, int freq)
{
    /*
    The one line of code looks scary, but here is the break down:
    'this->index[word]' will return an unordered_map<string, int>.
    even if the string 'word' is not originally a key, it will create a
    new key as 'word' and then return a neww unordered_map<string, int>

    The second part '[docID] += freq' will create a new key and stores an freq.
    Since all the document IDs are supposed to be unique, there won't be a
    case where calling [docID] will return an already existing bucket. (This
    is true because having the same word be on the same page is recoreded in
    the int 'freq' and won't be added to the index till at least after reading
    the page is done) Just in case there is an attempt to effectively re-read a
    page and there already exists an entry with 'word' with an entry equal to
    'docID' we use the '+=' operator since the intial state is 0 anyway.
    */
    this->index[word][docID] += freq;
}

void HashTableInterface::loadIndex()
{
  ifstream fin(this->indexFilePath.c_str());
  if(fin)
  {
    //clear the index
    clearIndex();

    //each entry will be of this form:
    /* [word] [docID] [freq] [otherDocId] [freq] ... */
    string line;
    while(fin.good())
    {
      getline(fin, line);

      stringstream stream(line);
      string word;
      stream >> word;
      //line is formatted wrong or we've reached the end
      // of the file without triggering an eof_bit flag
      if(word == "")
        continue;
      // add the word to the index
      this->index[word];

      while(stream.good())
      {
        // first entry will be a doc id, then an integer word frequency
        string id;
        int freq;
        stream >> id;
        stream >> freq;
        // if id is not set, then we have reached the end of the line
        // before any 'bad' flag in the stream was raised
        if(id == "")
          break;
        this->index[word][id] += freq;
      }
    }
  }
  else {
    // issue warning
    cerr << "The index file '" << this->indexFilePath <<
      "' could not be opened" << endl;
  }
}

unordered_map<string, int> HashTableInterface::searchIndex(string word)
{
    // this is a case where if the word is not already there
    // it will create a new key for it.
    return this->index[word];
}

void HashTableInterface::clearIndex()
{
    this->index.clear();
}

void HashTableInterface::writeIndex() const
{
    ofstream fout(this->indexFilePath.c_str());
    if(fout)
    {
        print(fout);
    }
    else
        throw logic_error("Error creating index file");
    fout.close();
}

void HashTableInterface::writeIndex(ostream& out) const
{
    print(out);
}

unordered_map<string, unordered_map<string, int> > HashTableInterface::getIndex() const
{
    return this->index;
}

void HashTableInterface::setIndex(unordered_map<string, unordered_map<string, int> >& map)
{
    this->index = map;
}
