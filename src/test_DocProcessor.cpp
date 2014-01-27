
#include <sstream>
#include <chrono>
#include "DocProcessor.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"

using namespace std;

int main(int argc, char** argv)
{
	DocProcessor processor;
	processor.buildFileStructure();
	chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	IndexHandler handler(true);
	end = chrono::system_clock::now();
	unsigned int duration = chrono::duration_cast<std::chrono::seconds>(end-start).count();
	cout << "It took '" << duration << "s' to initialize the index with the current index state on disk." << endl;
	processor.setHandler(handler);
	QueryProcessor q;
	q.setHandler(handler);
	q.setProcessor(processor);
	// handler.clearIndex();
	try
	{
		// int number = 10;
		
  //       start = std::chrono::system_clock::now();
		// for(int i = 1; i <= number; i++)
		// {
		// 	stringstream file;
		// 	file << "../WikiDump/WikiDumpPart";
		// 	file << i << ".xml";
		// 	if(i%10 == 0) cout << "Reading File " << i << endl;
		// 	        //Sort the data, and time the results

  //       	processor.readDocs(file.str().c_str());
		// }
		// end = chrono::system_clock::now();
  //       duration = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
  //       cout << "Reading '" << number << "' files filled with 1000 documents each took '" << duration << "ms'" << endl;

		cout << "Testing the QueryProcessor : " << endl << endl;

		string query = "chemistry";
		start = std::chrono::system_clock::now();
		vector<string> v = q.query(query);
		end = chrono::system_clock::now();
		duration = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
		cout << "Query, '" << query << "', took '" << duration << "' ms" << endl;

		cout << endl << endl;
		for(int i = 0; i < v.size(); i++)
		{

			cout << "id = '" << v[i].substr(0, 31) << "' tf/idf = '" << v[i].substr(32) << "' title: ";
			vector<string> doc = processor.load(v[i].substr(0, 31));
			cout << doc[0] << endl;
		}

	}
	catch(logic_error& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
