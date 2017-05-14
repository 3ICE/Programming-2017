/** This file is responsible for the CLI and core logic.
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
//It is recommended to write the include statements of C++ standard libraries
//below the include statements of the other modules.
#include "queue.hh"
#include "stack.hh"
#include <iostream>
#include <regex>
#include <string>

using namespace std;

//3ICE: using regular expressions to implement the user interface
//UPDATE: Was a really bad idea. Optional capture groups would have helped
//Maybe...
//3ICE: Anyway, here's a regex builder that removes leading and trailing spaces
const string TRIM = "\\ *";
regex make_regex(const string& middle){
    return regex(TRIM + middle + TRIM);
}

//3ICE: Does this help with readability? Maybe...
const string SPACE = "\\ +";

const regex INIT = make_regex("init" + SPACE + "([0-9]+)");
//3ICE: Dumb versions of almost every regex were necessary because messages
//3ICE: for errors had to be different for each situation. The automated tester
//3ICE: might not care, but I'm prepared for thorough manual testing.
const regex INIT_STUPID = make_regex("init" + SPACE + "(.*)");

//3ICE: Even worse, sometimes I wasn't allowed to use the optimal regex [0-9]+
const regex ADD = make_regex("add" + SPACE + "(.*?)" + SPACE + "(.*)");
//3ICE: Because of these stupid, stupid requirements.
const regex ADD_EXTRA_STUPID = make_regex("add" + SPACE + "([^0-9]+)" +
                                          SPACE + "(.*)");
const regex ADD_STUPID = make_regex("add" + SPACE + "([0-9]+)");

//3ICE: How relaxing, only one regex per command for these two.
const regex PRINT = make_regex("print");
const regex NEXT = make_regex("next");

//3ICE: Even better, zero regex needed for this command!
//const regex QUIT = make_regex("quit .*");

//3ICE: Back in crazy land again :(
//const regex ERASE = make_regex("erase" + SPACE + "([0-9]+)");
const regex ERASE_STUPID = make_regex("erase" + SPACE + "(.+)");

//3ICE: Helper function for comparing the beginning of two strings -- UNUSED
bool begins_with(const string& a, const string& b){
    return a.size() >= b.size() && equal(b.begin(), b.end(), a.begin());
}

//3ICE: Helper function for capturing the first word (the "command")
string first_word(const string& sentence){
    return sentence.substr(0, sentence.find(" "));
}

//3ICE: CLI handling and all core logic happens in here.
int main() {
    //3ICE: A stack of queues is perfect for this. A priority queue if you will
    Stack<Queue> db;
    //3ICE: I also experimented with: Stack<Stack<string>> db;

    //3ICE: Regular expression result set (with queryable capture groups)
    smatch result;

    //3ICE: What does the fox say? User input.
    string input;
    //3ICE: and also the first word:
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
                    //and then breaking the point of using regex... Just, no.
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
                    //cout<<"adding"<<endl;
                    db.push_back(priority, task);
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
                //I could have gotten away with the use of no regex here
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
                if(!db.empty(i)) {
                    db.pop_front(i, task);
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
            //catch one stupid (required) error. This task really upset me.
            if(!regex_match(input, result, ERASE_STUPID)){
                cerr << "Error: the running number is missing." << endl;
                continue;
            }
            int id;
            //3ICE: Why do you make me do this... If I was allowed to use ERASE
            //3ICE: instead of ERASE_STUPID, the regex would have made sure the
            //3ICE: number is a number. But now I need try-catch AND if-else...
            try{
                id = stoi(result.str(1));
            } catch(...){
                id = 0;
            }
            if(id==0){
                //3ICE: Or if it's not a number at all.
                cerr << "Error: the running number must be larger than 0."
                     << endl;
                continue;
            }
            if(!db.erase(id)){
                cerr << "Error: there is no such chore." << endl;
            }
            //Else: Do nothing :) Yes, zero output.
        }
        else if(command== "quit"){
            //Handled in the while loop condition.
            //Even if there is extra text on the command line after "quit"
            //Such as "quit 1". Thankfully.
        } else{
            cerr << "Error: bad or unknown command." << endl;
        }
    }
}
