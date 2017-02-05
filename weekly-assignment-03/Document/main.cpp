#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>


using namespace std;

// Splitter class from weekly-assignment-03:
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

class Document{
public:
    Document();

    void from_string(const string& str);
    bool from_file(const string& path);

    bool set_width(int w);
    bool set_height(int h);

    void print()const;

private:
    vector<string> words_;

    unsigned int w_;
    unsigned int h_;
};

Document::Document(): words_({}), w_(50), h_(40){}

void Document::from_string(const string& str){
    Splitter s(str);
    for(unsigned int i = 0; i < s.split(' ', true); ++i){
        words_.push_back(s.fetch_field(i));
    }
}

bool Document::from_file(const string& path){
    ifstream file(path);
    if(!file){
        cout<<"File "<<path<<" not found!"<<endl;
        return false;}
    string line;
    while(getline(file, line)){from_string(line);}
    file.close();
    return true;
}

bool Document::set_width(int w){
    if(w < 1){return false;}
    w_ = w;
    return true;
}

bool Document::set_height(int h){
    if(h < 1){return false;}
    h_ = h;
    return true;
}

void Document::print()const{
    unsigned int line_number = 0;
    vector<string>::const_iterator it = words_.begin();
    while(it != words_.end()){
        string line = "";
        while(it != words_.end()){
            if(line.empty() && it->size() >= w_){
                line = *it;
                ++it;
                break;
            }else if(line.size() + it->size() + 1 <= w_){
                if(!line.empty()){line += " ";}
                line += *it;
                ++it;
            }else{break;}
        }
        cout << line << endl;
        if(it == words_.end()){break;}
        ++line_number;
        if(line_number == h_){
            cout << string(w_, '-') << endl;
            line_number = 0;
        }
    }
}

int main(){
    Document doc;

    doc.from_file("the_best_day_ever.txt");

    cout << "12345678901234567890123456789012345678901234567890" << endl;
    doc.set_width(45);
    doc.set_height(10);
    doc.print();
}

//----------------------------------------------------------------------------
/* Let's implement a C++ class Document that can be used to pretty print
strual documents from a C++ program. The idea is that the document's str can
somehow be input from a keyboard or a .txt file. After the Document object has
been initialized it can be output on the screen in a somewhat neat(?) format.

Once the class is finished its public interface should offer at least the
following mechanisms for interacting with the str:

* A content of a string can be appended to the end of the document.
* A content of a .txt file can be appended to the end of the document.
* A document can be printed on the screen in such a way that no line is
  longer than some user defined number of characters (including whitespaces).
* When printing the document on screen there has to be some way to set the
  size of a page in lines. On the the screen the pages are separated with a
  line of '–'-characters or something similar.

Hint: When string type input is read either from a keyboard (cin) or from a
file using >>-operator, the reading happens one word at a time. This might be
useful to know. Also, if you have implemented the Splitter class before
starting this problem it might make it even easier. */
//----------------------------------------------------------------------------
