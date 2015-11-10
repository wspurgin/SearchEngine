/*
"UI" implementation file
*/

#include "UI.h"

using namespace std;

UI::UI(string indexFilePath)
{
    cout << "Initializing." << endl;
    this->handler = new IndexHandler(false, indexFilePath);
    this->query_processor.setHandler(*(this->handler));
    this->doc_processor.setHandler(*(this->handler));

    mode = -1;
}

UI::UI(const UI& rhs)
{
    this->handler = rhs.getHandler();
    this->doc_processor = rhs.getDocProcessor();
    this->query_processor = rhs.getQueryProcessor();
    mode = -1;
}

UI::~UI()
{
  delete this->handler;
}

int UI::launch()
{
    cout << "Welcome to MustangWiki Search!" << endl;
    if (ch_mode() != 0)
      return waitForCommand();
    else
      return 0;
}

IndexHandler* UI::getHandler() const { return this->handler; }

DocProcessor UI::getDocProcessor() const { return this->doc_processor; }

QueryProcessor UI::getQueryProcessor() const { return this->query_processor; }

//private internal functions

int UI::waitForCommand()
{
  while(true) {
    cout << ">";
    string cmd;
    getline(cin, cmd);
    cout << endl;
    if(analyzeCommand(cmd) == 0)
      break;
  }
  return 0;
}

int UI::analyzeCommand(string cmd_line)
{
    if(cmd_line == "")
        return 1;
    bool override = false;
    if(cmd_line.front() == ':') //user has entered global command
    {
        override = true;
        cmd_line.erase(cmd_line.begin());
    }

    //open string in stream
    stringstream cmd_stream(cmd_line);
    string cmd;
    cmd_stream >> cmd;
    //cmd is the actual command rather than just arguments
    toLower(cmd);

    //check global commands
    if(cmd == "quit")
        return quit();
    else if(cmd == "help")
        return help();
    else if(cmd == "ch-mode")
        return ch_mode();

    //check mode specfic commands
    if(this->mode == 1 || override) //interactive mode
    {
        if(cmd == "search")
        {
            //send the rest of the line minus the 'search' at the beginning
            // to the search function.
            cmd_line.erase(cmd_line.begin(), cmd_line.begin()+6);
            //trim leading white space
            while(cmd_line.front() == ' ')
                cmd_line.erase(cmd_line.begin());
            return search(cmd_line);
        }
        else if(cmd == "build-as-ht")
            return build_as_ht();
        else if(cmd == "build-as-avl")
            return build_as_avl();
    }

    if(this->mode == 2 || override)
    {
        if(cmd == "add")
        {
            //Need to get the rest of the line minus 'add'
            cmd_line.erase(cmd_line.begin(), cmd_line.begin()+3);
            //trim leading whitespace
            while(cmd_line.front() == ' ')
                cmd_line.erase(cmd_line.begin());
            return add(cmd_line);
        }
        else if(cmd == "clear-index")
            return clear_index();
    }

    if(this->mode != 3)
    {
        cout << "No command '" << cmd << "' write 'help' if you need it." << endl;
        return 1;
    }
    return 0;
}

int UI::quit()
{
    //at the moment no data clean up required
    return 0;
}

int UI::search(string query)
{
    //trim leading whitespace
    while(query.front() == ' ')
        query.erase(query.begin());

    cout << "query = '" << query << "'" << endl;

    //check if query is properly formatted
    stringstream sin(query);
    string temp;
    string keywords[] = {"AND", "NOT", "OR"};
    int count_before_keyword = 0;
    bool first_keyword = false;
    bool bad = false;

    //check for first key word or if query is just one word.
    while(sin >> temp)
    {
        if(temp == keywords[0] || temp == keywords[1] || temp == keywords[2])
            first_keyword = true;
        else if(!first_keyword)
            count_before_keyword++;
        if(count_before_keyword > 1)
        {
            //query is bad, too many words with no keyword
            bad = true;
            break;
        }
    }

    sin.seekg(0, sin.beg); // reset to beginning of query

    if(bad)
    {
        cout << "Improperly formatted query, type 'help' if you need it" << endl;
        return 1;
    }

    //check for the number of words after keywords
    int count_after_keyword = 0;
    string current_keyword = "";
    while(sin >> temp)
    {
        if(temp == keywords[0] || temp == keywords[1] || temp == keywords[2])
        {
            if(current_keyword == "AND" && count_after_keyword < 2)
            {
                bad = true;
                break;
            }
            else if( (current_keyword == "NOT" || current_keyword == "OR") && count_after_keyword < 1)
            {
                bad = true;
                break;
            }
            current_keyword = temp;
            count_after_keyword = 0;
            continue;
        }
        else
            count_after_keyword++;
    }

    if(bad)
    {
        cout << "Improperly formatted query, type 'help' if you need it" << endl;
        return 1;
    }
    else
    {

        //send to query_processor
        vector<string> results = this->query_processor.query(query);
        if(results.empty())
        {
            cout << "No documents found matching the query, '" << query << "'" << endl;
            if(this->mode != 3)
              return 1;
        }
        else
        {
            for(int i = 0; i < results.size(); i++)
            {
                // cout << results[i] << endl;
                try
                {
                    vector<string> doc = this->doc_processor.load(results[i].substr(0, 31));
                    if(doc.size() > 1)
                    {
                        cout << " title: '";
                        cout << doc[0] << "' author: '" << doc[1];
                        cout << "' tf/idf = '" << results[i].substr(32) << "'" << endl;
                    }
                    else;
                }
                catch(exception& e)
                {
                    cout << e.what() << endl;
                    return 1;
                }
            }
        }

        if(this->mode == 3) //stress-test mode
            return 0;

        return 1;
    }
}

int UI::build_as_ht()
{
    if(this->mode != 3)
    {
        cout << "Warning, you are trying to change the underlying structure of "
            << "the index." << endl << "This action is permitted, BUT you should\
            proceed only if you know what you're doing." << endl
            << "Continue? [Y/n]> ";
        char choice;
        try
        {
            cin >> choice;
            choice = tolower(choice);
            if(choice == 'y')
            {
                if(!this->handler->setUpIndex())
                    cout << "Errors have occured attempting to build Index as Hash Table." << endl;
            }
            else
              cout << "Cancelled." << endl;

            return 1;
        }
        // TODO catch specific error, not just exception
        catch(exception& e)
        {
            cout << "Cancelled." << endl;
            return 1;
        }
    }
    else
    {
        if(!this->handler->setUpIndex())
            cout << "Errors occured when attempting to build Index as Hash Table" << endl;
    }
    return 0;
}

int UI::build_as_avl()
{
    if(this->mode != 3)
    {
        cout << "Warning, you are trying to change the underlying structure of "
            << "the index." << endl << "This action is permitted, BUT you should\
            proceed only if you know what you're doing." << endl
            << "Continue? [Y/n]> ";
        char choice;
        try
        {
            cin >> choice;
            choice = tolower(choice);
            if(choice == 'y')
            {
                if(!this->handler->setUpIndex())
                    cout << "Errors have occured attempting to build Index as AVL Tree." << endl;
            }
            else
              cout << "Cancelled." << endl;

            return 1;
        }
        // TODO catch specific error, not just exception
        catch(exception& e)
        {
            cout << "Cancelled." << endl;
            return 1;
        }
    }
    else
    {
        if(!this->handler->setUpIndex())
            cout << "Errors occured when attempting to build Index as AVL Tree" << endl;
    }
    return 0;
}

int UI::add(string filePath)
{

  try
  {
    if(filePath == "all")
    {
      //number of wiki 'Part' files
      int number = (171000/this->doc_processor.getBlockSize()) + 1;

      for(int i = 1; i <= number; i++)
      {
        stringstream file;
        file << "../WikiDump/WikiDumpPart";
        file << i << ".xml";
        if(i%10 == 0) cout << "Reading File " << i << endl;
        //Sort the data, and time the results

        this->doc_processor.readDocs(file.str().c_str());

      }
      if(this->mode != 3)
        return 1;
    }
    else
    {
      this->doc_processor.readDocs(filePath.c_str());
      if(this->mode != 3)
        return 1;
    }
  }
  catch(logic_error& e)
  {
    cout << e.what() << endl;
    return 1;
  }
  /*
     If something unaccounted for happens but we get here without
     any errors and we are not in stress-test mode. Return 0 will
     let the program exit gracefully.
     */
  return 0;
}

int UI::clear_index()
{
    if(this->mode != 3)
    {
        cout << "Warning, you are trying to completely clear "
            << "the index.\nThis action is permitted, BUT you should proceed only"
            << "if you know what you're doing.\nType 'Y' to continue, 'n' to"
            << " cancel" << endl;
        char choice;
        try
        {
            cin >> choice;
            choice = tolower(choice);
            if(choice == 'y')
            {
                this->handler->clearIndex();
                    cout << "Errors have occured attempting to build Index as AVL Tree." << endl;
            }
            else
                cout << "Cancelled" << endl;
            return 1;
        }
        catch(exception& e)
        {
            cout << "Cancelled." << endl;
            return 1;
        }
    }
    else
        this->handler->clearIndex();
    return 0;
}

int UI::help()
{
    ifstream fin(".ui_man");
    if(fin)
    {
        char* help_text;
        fin.seekg(0, fin.end);
        int length = fin.tellg();
        fin.seekg(0, fin.beg);

        help_text = new char[length];
        fin.read(help_text, length);
        fin.close();
        cout.write(help_text, length);
        delete[] help_text;

        if(this->mode != 3)
            return 1;
    }
    else
    {
        cout << "Could not open .ui_man for help text." << endl
            << "Please refer to the user manual in doc" << endl;
        if(this->mode != 3)
            return 1;
    }
    return 0;
}

int UI::ch_mode()
{
    string u_mode;
    bool goOn = false;
    while(!goOn)
    {
        cout << endl << "Please enter mode:\ninteractive\nOR\nmaintenance\nOR\nstress-test" << endl;

        cout << ">";
        cin >> u_mode;
        cout << endl;

        toLower(u_mode);

        if(u_mode ==  "interactive")
        {
            this->mode = 1;
            goOn = true;
        }
        else if(u_mode == "maintenance")
        {
            this->mode = 2;
            goOn = true;
        }
        else if(u_mode == "stress-test")
        {
            this->mode = 3;
            goOn = true;
        }
        else if(u_mode == "quit")
            return quit();
        else
            cout << "No mode '" << u_mode << "'. Please enter either 'interactive', 'maintenance', or 'stress-test'" << endl;
    }
    cout << "Entering " << u_mode << " mode." << endl;
    if(this->mode == 3)
        stress_test();
    return 1;
}

int UI::stress_test()
{
    cout << "Please enter the path to the file containing the stress-test "
        << "commands.\nEvery line of this file should contain a command"
        << " followed by any command arguments (if needed).\n"
        << "Each of the commands will be timed, with the result being"
        << "being\n displayed in milliseconds" << endl;
    cout << "Type 'quit' to exit stress test mode" << endl;
    string file_path;
    bool goOn = false;
    while(!goOn)
    {
        cout << endl;
        cout << ">";
        cin >> file_path;
        cout << endl;
        if(file_path == "quit")
        {
            cout << "Exiting stress-test mode." << endl;
            cout << "Moving to interactive mode." << endl;
            this->mode = 1;
            return 1;
        }
        ifstream fin(file_path);
        if(fin)
        {
            string command;
            chrono::time_point<std::chrono::system_clock> start, end;
            unsigned int duration;
            while(getline(fin, command))
            {
                start = std::chrono::system_clock::now();
                analyzeCommand(command);
                end = chrono::system_clock::now();
                duration = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
                cout << "Command '" << command << "' took " << duration << "ms to complete" << endl;
            }
            cout << endl  << endl << "Finished All commands in the file '"
                << file_path << "'." << " Moving to interactive mode." << endl;
            this->mode = 1;
            goOn = true;
        }
        else
        {
            cout << "Could not open the file '" << file_path << "'. Please try again" << endl;
            goOn = false; // to be extra sure
        }
    }
    return 1;
}

void UI::toLower(string& str)
{
    for(int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
}
