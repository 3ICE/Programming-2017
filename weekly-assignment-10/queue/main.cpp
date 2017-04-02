#include <iostream>
#include "queue.hh"

using namespace std;


int main() {
    Queue patients;

    patients.add_to_end("Jack");
    patients.add_to_end("Jill");
    patients.add_to_end("Ann");
    patients.add_to_end("Bill");

    patients.print();

    string who;

    while ( patients.remove_from_front(who) ) {
        cout << "patent: " << who
             << " was removed from the queue." << endl;

        cout << "The patients who are still left in the queue:"
             << endl;
        patients.print();
    }
}
