/*
Will Spurgin
Test file creation
So we don't kill ourselves
11/12/2013
CSE 2341 - Data Structures
Seach Engine Project
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		cout << "USAGE: ./executable <output_filename> <number_of_docs>"
			<< endl;
		return 1;
	}
	const char* file = "enwikibooks-20131101-pages-meta-current.xml";
	
	ifstream fin(file);

	if(fin)
	{
		ofstream fout(argv[1]);
		
		//get the number of documents
		int number = atoi(argv[2]);
		char c = fin.peek();
		int doc_end;
		for(int i = 0; i < number; i++)
		{
			bool end = false;
			while(!end && fin.good())
			{
				c = fin.peek();
				while(c != '/' && fin.good())
				{
					fin.ignore(256, '<');
					c = fin.peek();
				}
				//move the file pointer 1 character forward
				string temp;
				fin >> temp;
				if(temp.substr(0, 5) == "/page")
				{
					end = true;
					//there might be a space after /page
					//so check if the last character in temp
					//is '>'
					if(temp.back() == '>')
						doc_end = fin.tellg();
					else
					{
						fin.ignore(20, '>');
						//now we've skipped any whitespace
						fin.ignore(1, '\n');
						doc_end = fin.tellg();
					}
				}
				else
				{
					c = fin.peek();
				}
			}		
		}
		char* buffer;
		try
		{	
			buffer = new char[doc_end+1];
		}
		catch(bad_alloc& e)
		{
			cout << e.what() << endl;
		}
		fin.seekg(0, fin.beg);
		fin.read(buffer, doc_end);
		if(fin)
		{
			cout << "Read " << doc_end << " characters, appending NULL" << endl;
			buffer[doc_end+1] = '\0';
			fout << buffer << endl;
		}
		else
		{
			cout << "error, only " << fin.gcount() << " chars could be read" << endl;
		}
		delete[] buffer;
		fout.close();
		fin.close();
	}
	else
	{
		cout << "The main document file '" << file << "' was expected to be in"
			<< " the same directory as this executable. The file was not found"
			<< endl;
		return 1; 
	}
	return 0;
}