/*
Nastasha Gerlt, Will Spurgin
12/7/2013
Search Engine - Data Structures
main routine
*/

#include "UI.h"

using namespace std;

int main(int argc, char** argv)
{
  string indexFilePath;
  if (argc < 2)
    indexFilePath = nullptr;
  else
    indexFilePath = argv[1];

  UI ui(indexFilePath);
  return ui.launch();
}
