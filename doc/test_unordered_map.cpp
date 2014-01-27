
#include "../src/IndexWord.h"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
	typedef IndexWord::IdRankingPair IdRankingPair;

	unordered_map<string, IdRankingPair> map;
	map.insert(make_pair<string, IdRankingPair>("compare", IdRankingPair("id", 6)));
	map["test"];
	IdRankingPair* pair = &map["test"];
	pair->docID = "39iahhfd372337";
	pair->termFrequency = 54;
	for(auto& x: map)
		cout << x.first << " : " << x.second << endl;

	unordered_map<string, int> other;
	other["shit"]++;
	for(auto& x: other)
		cout << x.first << " : " << x.second << endl;

	return 0;	
}
