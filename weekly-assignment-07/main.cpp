#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class Student {
public:
    string name;
    unsigned int id;
    bool operator<(const Student&b);
    bool operator<(const Student*b);
};


// ***** TODO *****************************************************************
// Implement a comparator function here. The function should be
// such that it can be used as a parameter to STL algorithm library's
// sort function.  It must be able to compare two Student type structs
// and the one whose name is earlier in alphabetical order should be
// interpreted as the smaller.
// ****************************************************************************
bool Student::operator<(const Student&b){return this->name < b.name;}
//cout<<this->name<<b.name;


// ***** TODO *****************************************************************
// Implement a comparator function here. The function should be
// such that it can be used as a parameter to STL algorithm library's
// sort function.  It must be able to compare two pointers to a Student
// type struct and the one that points to a student whose student id is
// smaller should be interpreted as the smaller pointer.
// ****************************************************************************
//bool Student::operator<(const Student*b){return this->id < b.id;}
bool g(const Student*a, const Student*b){
    return a->id < b->id;
}
//cout<<this->id<<b.id;


int main() {
    vector<Student> studentregistry = {
        { "Teekkari, Tiina",           52401 },
        { "Ylikuuskajaskari, Jaska",  186112 },
        { "Repolainen, Reijo",        117118 },
        { "Teekkari, Teemu",          196196 },
        { "Santaholma, Santtu",       173421 },
    };

    vector<Student*> studentpointers = { };

    // Let's initialize the pointer vector with the addresses of the
    // students in the studentregistry vector.
    for ( vector<Student>::size_type i = 0; i < studentregistry.size(); ++i ) {
        studentpointers.push_back( &studentregistry.at(i) );
    }



    // ***** TODO *************************************************************
    // At this point, use algorithm library's sort function to order
    // elements of the studentregistry vector into an aplhabetical order.
    // ************************************************************************
    sort(studentregistry.begin(), studentregistry.end());

    // ***** TODO *************************************************************
    // At this point, use algorithm library's sort function to order
    // elements of the studentpointers vector into increasing order
    // by the student id.
    // ************************************************************************
    sort(studentpointers.begin(), studentpointers.end(), g);


    //------------------------------------------------------------------
    // Here both of the arrays should now be sorted in the order that
    // is pictured in the assignment's documentation.
    //------------------------------------------------------------------



    // Test prints.  Did we actually succeed in
    // ordering the vectors as required?

    cout << "Students sorted in alphabetical order:" << endl
         << "--------------------------------------" << endl;
    for ( Student stu : studentregistry ) {
        cout << setw(24) << left << stu.name
             << setw(6) << right << stu.id << endl;
    }

    cout << endl;

    cout << "Students sorted by the student id:" << endl
         << "----------------------------------" << endl;
    for ( Student* stu_ptr : studentpointers ) {
        cout << setw(24) << left << stu_ptr->name
             << setw(6) << right << stu_ptr->id << endl;
    }
}
