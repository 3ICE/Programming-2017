/** 3ICE: This assignment is quite forced. I tried to vary it up,
 * but still there's no point to using the recursive function
 * I wrote over the reference one provided.
 */
#include <iostream>
#include <map>

using namespace std;

/** 3ICE: recursive function that returns the number of people in a phonebook
 * whose name begins with a specified letter
 * can change the number and types of parameters if you feel it is neccessary
 * return value stays the same: number whose name begin with the initial letter
*/
int count_names(int already_found, const map<string, string>& phonebook,
                map<string, string>::const_iterator it, char initial_letter) {
    if ( it != phonebook.end() ) //3ICE: Using "true=1" to avoid another if...
        return count_names(already_found + (it->first.at(0) == initial_letter),
                           phonebook, ++it, initial_letter);
    //3ICE: Else branch:
    return already_found;
}


/** 3ICE: Testing my recursive function... */
int main(/*int argc, char *argv[]*/){
    //The key field of the map (first) is name and payload (second) is phone number.
    map<string, string> test{ //3ICE: Phonebook
        { "Daniel", "+36 30 123 45 67" },
        { "Daniel's finnish number", "+358 40 123 45 67" },
        { "Somebody who is not Daniel", "0123456789" }
    };
    cout << "The test phonebook has ```" << count_names(0, test, test.begin(), 'D')
         << "``` names that begin with 'D'. Counted recursively (for whatever reason)." << endl;
    //cout << count_names_reference(test, 'S')<<endl;
    return 0;
}
