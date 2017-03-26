/** Minified Splitter class from weekly-assignment-03 (a split tool,
 * implementing a class Splitter, which has a suitable public
 * interface to do splitting related operations)
 *
 * @note This time I'm going to put all function documentation in the
 * other file. (splitter.cpp)
 * @see splitter.cpp
 *
 * @question Does this comment block go inside the include guard or
 * is it okay to place it above? The generated source will contain
 * this comment more than once. But comments are not included in the
 * linking process anyway. No major side effect either way.
 *
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#ifndef SPLITTER_HH
#define SPLITTER_HH
//3ICE: There have to be at least three modules.
//3ICE: Use Splitter from exercise 03. Convert it into a module,
//3ICE: will conveniently be one of the modules required in this project.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

/** Splitter class. Takes a string and breaks it into parts
 * along a single separator character.
 * @see splitter.cpp for ALL documentation. (As opposed to the
 * case of data.hh and data.cpp where I documented both files.)
 * This file only has class-level and variable documentation.
 * No methods, those are explained in splitter.cpp this time.
 */
class Splitter {
private:
    /** fields is an array holding the exploded string
     */
    std::vector<std::string> fields;
    /** str is a string holding the original text
     */
    std::string str;
    /** The character we split on is not saved. Nor is status ("done") kept track of.
      */
    //3ICE: Removed done.
public:
    Splitter(const std::string& string_to_split);
    void set_string_to_split(const std::string& string_to_split);

    //3ICE: Changed int → size_t to avoid these warnings:
    //"conversion from 'size_t' to 'int', possible loss of data"
    size_t split(char separator, bool ignore_empty = false);
    size_t number_of_fields() const;
    std::string fetch_field(unsigned int field_index) const;
    std::string operator[](size_t idx); //3ICE: Array-like indexing for convenience
};
#endif // SPLITTER_HH
