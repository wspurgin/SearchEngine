/*
Nastasha Gerlt, Will Spurgin
11/16/2013
Data Structures - Search Engine
'DocLoader' header file
*/

#include "DocLoader.h"

using namespace std;

DocLoader::DocLoader() { loadFileStructure(); }

DocLoader::DocLoader(const DocLoader& rhs)
{
	this->file_structure = rhs.getFileStructure();
}

DocLoader::~DocLoader()
{
	cout << "Writing file_structure out" << endl;
	writeFileStructure();
}

unordered_map<string, string> DocLoader::getFileStructure() const
{ cout << this << endl; return this->file_structure; }

void DocLoader::addIdPathPair(string id, string path) { this->file_structure[id] = path; }

vector<string> DocLoader::loadDocument(string id)
{
	string filePath = this->file_structure[id];
	try
	{

		//open file with rapidxml
		rapidxml::file<> file(filePath.c_str());
		rapidxml::xml_document<> doc;
		doc.parse<0>(file.data());
		rapidxml::xml_node<>* root_node = doc.first_node();
		vector<string> document_info;

		if(root_node == 0)
			cout << "Improperly formated XML" << endl;

		for(rapidxml::xml_node<>* page_node = root_node->first_node("page"); page_node;
			page_node = page_node->next_sibling())
		{
			rapidxml::xml_node<>* revision_node = page_node->first_node("revision");
			string sha1 = revision_node->first_node("sha1")->value();
			rapidxml::xml_node<>* contrib_node = revision_node->first_node("contributor");
			rapidxml::xml_node<>* username_node;
			if(contrib_node != NULL)
				username_node = contrib_node->first_node("username");	

			if(sha1 == id)
			{
				page_node != NULL ? document_info.push_back(page_node->first_node("title")->value()) : document_info.push_back("Title-Corrupted");
				username_node != NULL ? document_info.push_back(username_node->value()) : document_info.push_back("Unknown");
				revision_node != NULL ? document_info.push_back(revision_node->first_node("text")->value()) : document_info.push_back("NO TEXT");
				return document_info;
			}
		}
		document_info.push_back("No Document Found with id:'" + id + "'");
		return document_info;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
		throw exception(e);
	}
}

void DocLoader::loadFileStructure()
{
	struct stat st;
	if(stat("../file_structure.txt", &st) == 0)
	{
		ifstream fin("../file_structure.txt");
		if(fin)
		{
			while(fin.good())
			{
				string id;
				string path;
				fin >> id;
				fin >> path;
				addIdPathPair(id, path);
			}
		}
		else
			cerr << "Error opeing file_structure file" << endl;
	}
}

void DocLoader::clearFileStructure()
{
	this->file_structure.clear();
}

void DocLoader::writeFileStructure()
{
	ofstream fout("../file_structure.txt");
	if(fout)
	{
		for(auto& x : this->file_structure)
			fout << x.first << " " << x.second << endl;
	}
	else
		cout << "Couldn't open output file for current file_structure" << endl;
	fout.close();
}

DocLoader& DocLoader::operator=(const DocLoader& rhs)
{
	this->file_structure = rhs.getFileStructure();
	return *this;
}
