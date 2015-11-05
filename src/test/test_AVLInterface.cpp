
#include "AVLInterface.h"

using namespace std;

int main(int argc, char** argv)
{
    IndexWord temp("test");
    temp.rankingPairs["alj139843j12"] = 120;
    temp.rankingPairs["244jc232c23f"] = 45;

    ofstream fout("../index.txt");
    if(fout)
    {
        fout << temp << endl;
        temp.word = "run";
        temp.rankingPairs["alj139843j12"] = 19;
        temp.rankingPairs["244jc232c23f"] = 83;
        temp.rankingPairs["3jaf3di2034j"] = 64;
        fout << temp << endl;
    }
    else
    {
        cout << "Error opening '../index.txt'." << endl;
        return 1;
    }
    fout.close();
    cout << "Creating AVLInterface. It will load an index (during construction) from '../index.txt'." << endl;
    IndexHandler handler;
    
    return 0;
}

