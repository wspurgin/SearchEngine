/*
Nastasha Gerlt, Will Spurgin
11/16/2013
Data Structures - Search Engine
'DocProcessor' implementation file
*/

#include "DocProcessor.h"

using namespace std;

DocProcessor::DocProcessor()
{
	this->blockSize = 1000;
	this->fileStructureBuilt = false;
	this->handler = NULL;
	struct stat st;
	stat("../WikiDump", &st);
	if(S_ISDIR(st.st_mode))
		this->fileStructureBuilt = true;
}

DocProcessor::DocProcessor(int size)
{
	this->blockSize = size;
	this->fileStructureBuilt = false;
	this->handler = NULL;
	struct stat st;
	stat("../WikiDump", &st);
	if(S_ISDIR(st.st_mode))
		this->fileStructureBuilt = true;
}

DocProcessor::DocProcessor(const DocProcessor& rhs)
{
	this->blockSize = rhs.getBlockSize();
	this->fileStructureBuilt = rhs.isFileStructureBuilt();
	this->loader = rhs.getLoader();
	this->cleaner = rhs.getCleaner();
	this->handler = &rhs.getHandler();
}

DocProcessor::~DocProcessor() {}

int DocProcessor::getBlockSize() const
{
	return this->blockSize;
}

bool DocProcessor::isFileStructureBuilt() const
{
	return this->fileStructureBuilt;
}

unordered_map<string, int> DocProcessor::getAllFilesInIndex() const
{
	unordered_map<string, int> temp;
	unordered_map<string, string> ids = this->loader.getFileStructure();
	for(auto& x : ids)
		temp[x.first] = 0;
	return temp;

}

DocLoader DocProcessor::getLoader() const
{
	return this->loader;
}

StringCleaner DocProcessor::getCleaner() const
{
	return this->cleaner;
}


IndexHandler& DocProcessor::getHandler() const
{
	return *this->handler;
}


void DocProcessor::setBlockSize(int size)
{
	this->blockSize = size;
}

void DocProcessor::setFileStructureBuilt(bool isBuilt)
{
	this->fileStructureBuilt = isBuilt;
}

void DocProcessor::setLoader(const DocLoader& l)
{
	this->loader = l;
}

void DocProcessor::setCleaner(const StringCleaner& c)
{
	this->cleaner = c;
}


void DocProcessor::setHandler(IndexHandler& h)
{
	this->handler = &h;
}


vector<string> DocProcessor::load(string docID)
{
	if(!isFileStructureBuilt())
		throw logic_error("File Structure Not Built");
	else
		return loader.loadDocument(docID);
}

//given a file path
void DocProcessor::readDocs(const char* filePath)
{
	if(!isFileStructureBuilt())
		throw logic_error("File Structure Not Built");
	//open file with rapidxml parser

	try
	{
		rapidxml::file<> file(filePath);

		rapidxml::xml_document<> doc;
		doc.parse<0>(file.data());
		rapidxml::xml_node<>* root_node = doc.first_node();
		if(root_node == 0)
			cout << "Improperly formated XML" << endl;

		unordered_map<string, int> map;

		//start of for loop
		for(rapidxml::xml_node<>* page_node = root_node->first_node("page"); page_node;
				page_node = page_node->next_sibling())
		{
			map.clear();

			// grab text from an individual document
			rapidxml::xml_node<>* revision_node = page_node->first_node("revision");
			string text = revision_node->first_node("text")->value();
			string id = revision_node->first_node("sha1")->value();

			// go through the cleaned text and grab each word
			stringstream stream(text);
			
			while(stream.good())
			{
				string word;
				stream >> word;

				//clean the text
				word = this->cleaner.clean(word);

				/*
				create second stringstream out of word
				since the pre-cleaned word may have had multiple words
				that were read in all as one (e.g. "all-one-word" would be
				cleaned to "all one word" which is three individual words).
				*/
				stringstream cleaned(word);
				while(cleaned.good())
				{
					cleaned >> word;
					/*
					put the word in the map if not already there and increment
					the word frequency
					*/
					map[word]++;
				}
			}
			
			//add docuemnt id with the path to this file to the loader
			this->loader.addIdPathPair(id, filePath);

			//make sure the handler is actually set
			if(this->handler == NULL)
				throw logic_error("The Index Handler has not be set");

			//add all the words inside 'map'
			for(auto& x : map)
			{
				this->handler->addWord(x.first, id, x.second);
			}
		}
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
}

void DocProcessor::buildFileStructure()
{
	if(!isFileStructureBuilt() && blockSize > 0)
	{
		stringstream cmd;
		cmd << "perl wikibookssplitter.pl ../doc/enwikibooks-20131101-pages-meta-current.xml ";
		cmd << blockSize << " 1000 ../WikiDump";
		system(cmd.str().c_str());
	}
	else if(!(blockSize > 0))
	{
		//setting to default blockSize
		blockSize = 1000;
		buildFileStructure();
	}
	else;
		//do nothing
	this->fileStructureBuilt = true;
}

void DocProcessor::clearFileStructure()
{
	this->loader.clearFileStructure();
	system("rm -rf ../WikiDump");
}

DocProcessor& DocProcessor::operator=(const DocProcessor& rhs)
{
	this->blockSize = rhs.getBlockSize();
	this->fileStructureBuilt = rhs.isFileStructureBuilt();
	this->loader = rhs.getLoader();
	this->cleaner = rhs.getCleaner();
	this->handler = &rhs.getHandler();
	return *this;
}
