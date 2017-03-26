/** Minified Splitter class from weekly-assignment-03 (a split tool,
 * implementing a class Splitter, which has a suitable public
 * interface to do splitting related operations)
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "splitter.hh"

using namespace std;

/**
 * @brief Splitter::Splitter Creates a splitter object with the
 * given string. Constructor. This object can then be operated
 * on using the other methods: set_string_to_split, split(),
 * number_of_fields, fetch_field, and operator[]
 * @param string_to_split the string itself (optional)
 */
Splitter::Splitter(const string& string_to_split = ""){
    fields.clear();
    str = string_to_split;
}

/**
 * @brief Splitter::set_string_to_split we can also set the string
 * we want to split with this method.
 * One Splitter object can be used for splitting different strings.
 * @param string_to_split same as the constructor parameter
 */
void Splitter::set_string_to_split(const string& string_to_split){
    fields.clear();
    str = string_to_split;
}

/**
 * @brief Splitter::split The string will be split into parts/fields on a separator.
 * @param separator which character to consider the word boundary
 * @param ignore_empty legacy code, not used in this project. (If ignore_empty is true,
 * then the empty fields resulting from the split are ignored. This is a useful feature
 * if we are splitting a line of words separated by spaces and we don't know if there
 * is exactly one space between each word.)
 * @return how many fields did the string have
 */
size_t Splitter::split(char separator, bool ignore_empty){
    fields.clear();
    string buf = "";
    unsigned int i = 0;
    while(i < str.length()) {
        if(str[i] != separator)
            buf += str[i];
        else if(!ignore_empty) {
            fields.push_back(buf);
            buf = "";
        } else if(buf.length() > 0) {
            fields.push_back(buf);
            buf = "";
        }
        i++;
    }
    if(!buf.empty())
        fields.push_back(buf);
    //cout<<str<<endl;for(auto s:fields){cout<<s<<" ";}cout<<endl;
    return fields.size();
}

/**
 * @brief Splitter::number_of_fields is a simple wrapper for the
 * internal vector's size() function. (In principle the return
 * value is the same as what the split method returns.)
 * @return the number of fields that can be queried, resulting from
 * the previous split operation. Zero if split() has not been run yet.
 * @see split()
 */
size_t Splitter::number_of_fields() const{
    //3ICE: Removed SPLIT_ERROR.
    return fields.size();
}

/**
 * @brief Splitter::fetch_field Similar to .get() or .at() in vectors.
 * After the split has been done (using split method) the different
 * fields resulting from the split can be queried with fetch_field method.
 * The fields are numbered/indexed from zero up to an integer one less than
 * the number of the fields. If the index is too large compared to the
 * number of fields in the result this method throws out_of_range exception
 * @param field_index an integer from 0 to number_of_fields-1 (or size-1)
 * @return the element at the given index
 * @throws out of range exception if field_index >= number_of_fields
 */
string Splitter::fetch_field(unsigned int field_index) const{
    if(field_index >= fields.size()) throw out_of_range("too large index");
    return fields[field_index];
}

/**
 * @brief Splitter::operator [] same as fetch_field, but usable like this:
 * <code>
 * splitter s("hello world");
 * s.split(' ');
 * cout<<s[0]; //"hello"
 * string w = s[1] //w=="world"
 * </code>
 * @param idx the array index
 * @return the element at the given index
 */
string Splitter::operator[](size_t idx){
    if(idx > fields.size()) throw out_of_range("too large index");
    return fields[idx];
}

