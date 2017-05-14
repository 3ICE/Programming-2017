//It is recommended to write the include statements of C++ standard libraries
//below the include statements of the other modules.
#include "queue.hh"
#include "stack.hh"
#include "regexes.cpp"
#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

//3ICE: using regular expressions to implement the user interface
const string TRIM = "\\ *";
regex make_regex(const string& middle){
    return regex(TRIM + middle + TRIM);
}

const string SPACE = "\\ +";

const regex INIT = make_regex("init" + SPACE + "([0-9]+)");
const regex INIT_STUPID = make_regex("init" + SPACE + "(.*)");

const regex ADD = make_regex("add" + SPACE + "(.*)" + SPACE + "(.*)");
//3ICE: Stupid, stupid requirements.
const regex ADD_EXTRA_STUPID = make_regex("add" + SPACE + "([^0-9]+)" + SPACE + "(.*)");
const regex ADD_STUPID = make_regex("add" + SPACE + "([0-9]+)");

const regex PRINT = make_regex("print");
const regex NEXT = make_regex("next");
//const regex QUIT = make_regex("quit .*");

//const regex ERASE = make_regex("erase" + SPACE + "([0-9]+)");
const regex ERASE_STUPID = make_regex("erase" + SPACE + "(.+)");


bool begins_with(const string& a, const string& b){
    return a.size() >= b.size() && equal(b.begin(), b.end(), a.begin());
}

string first_word(const string& sentence){
    return sentence.substr(0, sentence.find(" "));
}


int main() {
    //3ICE: A stack of queues is perfect for this.
    Stack<Queue> db;

    //3ICE: Regular expression result set (with queryable capture groups)
    smatch result;

    string input;
    string command = "";

    while(command != "quit") {
        cout << "chores> ";
        cin.clear();
        getline(cin,input);

        //3ICE: Combination of regex and substr+find (But at least no strcmp)
        command = first_word(input);


        if(command== "init"){
            if(regex_match(input, result, INIT)){
                int size = stoi(result.str(1));
                if(size <= 0){
                    //3ICE: Don't you dare test with -1! Asking for regex,
                    //and then breaking the point of using regex... Just no
                    cerr << "Error: it is not possible to create a " <<
                            "priority list with 0 or less levels." << endl;
                } else {
                    db.init(size);
                    cout << "New priority list with levels 1-" << size
                         << " initialized." << endl;
                }
            } else {
                //3ICE: This is rather pointless. I know I asked for custom
                //error messages but now you went overboard - it's too much
                if(regex_match(input, result, INIT_STUPID)){
                    cerr << "Error: the number of priority levels must " <<
                            "be an integer larger than 0." << endl;
                } else {
                    cerr << "Error: the number of priority levels is " <<
                            "missing." << endl;
                }
            }
        }
        else if(command== "add"){
            if (regex_match(input, result, ADD)){
                int priority;
                //3ICE: Why do you make me do this?
                //if(regex_match(input, result, ADD_EXTRA_STUPID)){
                try{
                    priority = stoi(result.str(1));
                } catch(...){
                    priority = 0;
                }
                int size = db.size();
                if(priority > size || priority < 1){
                    cerr << "Error: priority level must be an integer "
                         << "between 1-" << size << "." << endl;
                } else {
                    string task = result.str(2);
                    db[priority-1].push_back(task);
                    cout << "New chore added to priority level "
                         << priority <<"." << endl;
                }

            } else {
                //3ICE: Again, too much error detail. The point of regular
                //expressions is to filter out all kinds of errors in one go
                //so when you ask me to provide unique error messages for
                //each kind of error I will of course call it ADD_STUPID
                if(regex_match(input, result, ADD_STUPID)){
                    cerr << "Error: chore description is missing." << endl;
                } else {
                    cerr << "Error: priority level and chore description "
                         << "are missing." << endl;
                }
            }
        }
        else if(command== "print"){
            if (regex_match(input, result, PRINT)){
                db.print();
            } else {
                //3ICE: If it wasn't for this unnecessary error message,
                //I could have gottan away with the use of no regex here
                //whatsoever. But at least there's no PRINT_STUPID now...
                cerr << "Error: extra text after print command." << endl;
            }
        }
        else if(command== "next"){
            if (!regex_match(input, result, NEXT)){
                cerr << "Error: extra text after next command." << endl;
                continue;
            }

            string task = "";
            for(int i=db.size()-1; i>=0; --i){
                if(!db[i].empty()) {
                    db[i].pop_front(task);
                    break;
                }
            }
            if(task == ""){
                cout << "--- no chores left ---" << endl;
            } else {
                cout << task << endl;
            }
        }
        else if(command== "erase"){
            //3ICE: Intentionally stupidifying my regex just so that I can
            //catch one stupid error (requirement) This task really upset me.
            if(!regex_match(input, result, ERASE_STUPID)){
                cerr << "Error: the running number is missing." << endl;
                continue;
            }
            int id;
            //3ICE: Why do you make me do this...
            try{
                id = stoi(result.str(1));
            } catch(...){
                id = 0;
                continue;
            }
            if(id==0){
                //3ICE: Or if it's not a number at all.
                cerr << "Error: the running number must be larger than 0."
                     << endl;
                continue;
            }
            if(db.erase(id)){
                //Do nothing :) Yes, zero output.
            } else {
                cerr << "Error: there is no such chore." << endl;
            }
        }
        else if(command== "quit"){
            //Handled in the while loop condition.
            //Even if there is extra text on the command line after "quit"
            //Such as "quit 1"
        }
        else{
            cerr << "Error: bad or unknown command." << endl;
        }
    }
}
