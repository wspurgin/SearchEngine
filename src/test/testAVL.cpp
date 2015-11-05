//test AVL tree

#include<iostream>
#include<string>
#include "AVLTree.hpp"
#include "IndexWord.h"
using namespace std;

int main()
{
	AVLTree<IndexWord> testTree;
    IndexWord word("test");
    word.rankingPairs["24fdjw9832"] = 7;
	testTree.insert(word);
    word.word = "another";
    word.rankingPairs["24fdjw9832"] = 98;
    word.rankingPairs["9ladf39233"] = 23;
	testTree.insert(word);
    IndexWord str("new");
    str.rankingPairs["289jafd235"] = 8;
	testTree.insert(str);
    str.rankingPairs["289jafd235"] = 34;
    str.rankingPairs["a39ifj23fd"] = 10;
    str.word = "more";
	testTree.insert(str);
	testTree.print();

return 0;
}
