/*
Nastasha Gerlt, Will Spurgin
11/29/2013
Search Engine - Data Structures
'AVLInterface' implementation file
*/

#include "AVLInterface.h"

AVLInterface::AVLInterface() : IndexInterface()
{
    loadIndex();
}

//AVLTree takes care of itself, no manual destruction needed
// but we want to write the index before the AVLTree is destroyed
AVLInterface::~AVLInterface()
{
    writeIndex();
}

/*
Copy Consturctor (AVLTree doesn't have a copy constructor) so we write the
current state of 'rhs' to it's indexFile then we copy that location to this
instance of AVLInterface and load the index. (might be better to have a
CpyCons, but for right now this works)
*/
AVLInterface::AVLInterface(const AVLInterface& rhs)
{
    rhs.writeIndex();
    this->indexFilePath = rhs.getIndexFilePath();
    this->loadIndex();
}


void AVLInterface::addWord(string word, string docID, int freq)
{
    //set up IndexWord object to give to index
    IndexWord iword(word);
    iword.rankingPairs[docID] = freq;

    //The AVLTree will handle if we are adding a word that already exisits
    //by simply adding the rankingPairs together.
    this->index.insert(iword);

    // Done adding the word to the index. Nice and simple.
}

// This will create an index out of the file specified in
// 'indexFilePath'
void AVLInterface::loadIndex()
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
      IndexWord temp;
      stream >> temp.word;
      //line is formatted wrong or we've reached the end
      // of the file without triggering an eof_bit flag
      if(temp.word == "")
        continue;
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

        temp.rankingPairs[id] = freq;
      }

      // add word to index
      this->index.insert(temp);
    }
  }
  else {
    // issue warning
    cerr << "The index file '" << this->indexFilePath <<
      "' could not be opened" << endl;
  }
}

//search the index for a given word

unordered_map<string, int> AVLInterface::searchIndex(string word)
{
    try
    {
        IndexWord result = this->index.find(word);
        return result.rankingPairs;
    }
    catch(logic_error& e)
    {
        throw logic_error(e);
    }
}

// clears index
void AVLInterface::clearIndex()
{
    this->index.makeEmpty();
}

//writes index to output file
void AVLInterface::writeIndex() const
{
  ofstream fout(this->indexFilePath.c_str());
  if(fout)
  {
    this->index.print(fout);
  }
  else
    throw logic_error("Error creating index file");
  fout.close();
}

void AVLInterface::writeIndex(ostream& out) const
{
    this->index.print(out);
}