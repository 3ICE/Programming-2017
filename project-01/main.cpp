/** This is the main program. It's short and sweet,
 * with most of the code lines handling user input.
 * It orchestrates the rest of the modules into a
 * unified harmony. Reads a file (test files provided
 * and their loader lines commented out), processes it,
 * then exposes a CLI (command line interface) for
 * running queries against said file's contents.
 *
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */

//One or two letter names aren't generally too good
//Every source file (.cpp and .hh) begin with a comment including your email address and student id.
//Every function definition is preceded by a comment describing what the function does, what is the purpose of each of its parameters, and what is the return value if any.
//Generally, the algorithms you use in your functions don't need to be commented, unless you feel you have come up with an idea/implementation you think might be hard for someone else to understand.

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include "product.hh"
#include "splitter.hh"
#include "data.hh"

using namespace std;

/** main is the core program logic, does everything described in the specification
 * @return 0 if "quit" was typed, -1 or -2 if there were errors in the input file
 */
int main(){
    /**
     * @brief database will hold all the information present in the CSV file.
     */
    data database;

    /**
     * @brief fin is the main file input stream. Its format is like CSV, and
     * four columns are expected. (market, store, product, and price)
     */
    ifstream fin("products.txt");

    //3ICE: I've kept the test files I created here, for your convenience.
    //Comment out products.txt↑ and then uncomment one line below to test.
    //ifstream fin("this-file-does-not-exist.txt");
    //ifstream fin("bad_8.txt"); //3ICE: A range of files: bad_1 .. bad_8
    //ifstream fin("products--cheapest-milk-sub-order-alphabetical-too.txt");
    //ifstream fin("products--same-more-than-once.txt");

    //3ICE: Quick check for file not found:
    if(!fin){
        cout << "Error: the input file can not be read." << endl;
        return -1;
    }

    /**
     * @brief line Holds the current line as we parse the CSV file.
     * @brief success Switches to false as soon as we encounter a fault
     */
    string line;
    bool success = true;

    //3ICE: I'm only allowed to read the input file once, so here goes:
    while(success && getline(fin, line)){
        success = database.process(line);
    }
    //3ICE: That's it, done! Close it right away:
    fin.close();

    //3ICE: Some other error occurred. Specification does not allow deviating from this error message
    if(!success){
        cout << "Error: the input file can not be read." << endl;
        return -2;
        //3ICE: I wish I could print custom error messages for each kind of error.
        //3ICE: Communicating the error message is handled by the database, but commented out.
        //@see: comments in data::process and data::add for my advanced error handling logic.
    }

    vector<string> args{""};

    //3ICE: The size check is to avoid index out of range error on empty lines:
    while(args.size()==0 || args[0]!="quit"){
        cout << "product search> ";
        cin.clear();
        string input;
        getline(cin,input);

        //3ICE: Using my splitter
        Splitter s(input);
        s.split(' ');
        args.clear();
        for(unsigned int i = 0; i < s.number_of_fields(); ++i) {
            args.push_back(s.fetch_field(i));
        }
        if(args.size()==0){
            //3ICE: What should I do if there's no input? Specification doesn't say.
            continue; //3ICE: I'm not going to print invalid command on no input.
        }
        string command = args[0]; //3ICE: Readability enhancer.
        if(command == "chains")
            if(args.size() == 1) database.chains();
            else cout << "Error: usage is [chains] (needs no command line parameters)" << endl;

        else if(command == "stores")
            if(args.size() == 2) database.stores(args[1]);
            else cout << "Error: usage is [stores marketplace] (needs one command line parameter)" << endl;

        else if(command == "selection")
            if(args.size() == 3) database.products(args[1], args[2]);
            else cout << "Error: usage is [selection marketplace store] (needs two command line parameters)" << endl;

        else if(command == "cheapest")
            if(args.size() == 2) database.cheapest(args[1]);
            else cout << "Error: usage is [cheapest product] (needs one command line parameter)" << endl;

        else if(command != "quit"){//3ICE: Avoid printing error message before quitting (visible for a split second)
            cout << "Error: \"" << input << "\" not recognized. "
                 << "Valid commands are: chains, stores, selection, cheapest, and quit" << endl;
            //3ICE: Specification does not dictate exact wording. But it has to be on one line.
        } //3ICE: Taking a big risk here, not using explicit curly braces
    } //3ICE: except with the last if block to avoid the dangling else problem.
    return 0;
}
