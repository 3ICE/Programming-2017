#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// unsigned int is a type you can use to store and manipulate
// natural numbers (N) in C++ programs. In other words
// whole numbers that are = 0.
const unsigned int SPLIT_ERROR = 0;

class Splitter {
public:
    Splitter(const string& string_to_split = ""){
        fields.clear();
        str=string_to_split;
        done=false;
    }

    // In addition to the constructor parameter we can also
    // set the string we want to split with this method.
    // The idea is that one Splitter object can be used
    // for splitting different strings at the different times
    // of the program execution.
    void set_string_to_split(const string& string_to_split){
        fields.clear();
        str=string_to_split;
        done=false;
    }

    // The string will be split into parts/fields on a separator.
    // Return value tells how many fields did the string have.
    // If ignore_empty is true, then the empty fields
    // resulting from the split are ignored. This is a useful
    // feature if we are splitting a line of words separated by spaces
    // and we don't know if there is exactly one space between each word
    unsigned int split(char separator, bool ignore_empty = false){
        fields.clear();
        string buf = "";
        int i = 0;
        while (i < str.length()) {
            if (str[i] != separator)
                buf += str[i];
            else if (!ignore_empty) {
                fields.push_back(buf);
                buf = "";
            } else if (buf.length() > 0) {
                fields.push_back(buf);
                buf = "";
            }
            i++;
        }
        if (!buf.empty())
            fields.push_back(buf);
        done=true;
        return fields.size();
    }

    // Returns the number of fields resulting from the
    // previous split operation. In principle the return
    // value is the same as what the split method returns.
    // There is one exception: return value is SPLIT_ERROR
    // in case the split method has not been called after
    // the string to be split was set (either in the constructor
    // or in the set_string_to_split method).
    unsigned int number_of_fields() const{
        if (done) {
            return fields.size();
        }
        return SPLIT_ERROR;
    }

    // After the split has been done (using split method)
    // the different fields resulting from the split can be
    // queried with fetch_field method. The fields are
    // numbered/indexed from zero up to an integer one less than
    // the number of the fields. If fetch_field is called
    // before split method or if the index is too large
    // compared to the number of fields in the result this
    // method results out_of_range exception
    string fetch_field(unsigned int field_index) const{
        if(field_index>fields.size() || !done)throw out_of_range("too large index or split not called");
        return fields[field_index];
    }

private:
    vector<string> fields;
    string str;
    bool done;
};

int main(/*int argc, char *argv[]*/){
    Splitter splitter_object("a::bc:def::hijlkm");

    splitter_object.split(':'); // Observe: single quotes: parameter is of type char.

    cout << "fields: " << splitter_object.number_of_fields() << endl; // 6

    cout << splitter_object.fetch_field(0) << endl; // a
    cout << splitter_object.fetch_field(4) << endl; // (empty)
    cout << splitter_object.fetch_field(5) << endl; // hijlkm

    for ( unsigned int i = 0; i < splitter_object.number_of_fields(); ++i ) {
        string current_field_contents = splitter_object.fetch_field(i);
        cout << i << ": [" << current_field_contents << "]" << endl;
    }

    splitter_object.set_string_to_split(" A B C  D  E   ");
    unsigned int fields = splitter_object.split(' ', true);

    cout << "fields: " << fields << endl; // 5

    for ( unsigned int i = 0; i < fields; ++i ) {
        string current_field_contents = splitter_object.fetch_field(i);
        cout << i << ": [" << current_field_contents << "]" << endl;
    }

    //cout << splitter_object.fetch_field(5) << endl; // out_of_range exception
    return 0;
}
