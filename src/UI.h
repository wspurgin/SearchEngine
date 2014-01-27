/*
Nastasha Gerlt, Will Spurgin
12/3/2013
Search Engine - Data Structures
"UI" header file
*/

#ifndef UI_H
#define UI_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <chrono>

#include "DocProcessor.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"

using namespace std;

class UI
{
private:
    IndexHandler handler;
    DocProcessor doc_processor;
    QueryProcessor query_processor;

    int mode;

    int waitForCommand();

    int analyzeCommand(string cmd_line);

    int quit();

    int search(string query);

    int build_as_ht();

    int build_as_avl();

    int add(string filePath);

    int clear_index();

    int help();

    int ch_mode();

    int stress_test();

    void toLower(string& str);

public:

    UI();

    UI(const UI& rhs);

    ~UI();

    int launch();

    IndexHandler getHandler() const;

    DocProcessor getDocProcessor() const;

    QueryProcessor getQueryProcessor() const;

};

#endif
