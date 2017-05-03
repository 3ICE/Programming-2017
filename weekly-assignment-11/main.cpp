#include <iostream>
#include "queue.h"

using namespace std;

int main(){
    cout<<"Hello!"<<endl<<"Adding 4, then removing 4 patients:"<<endl;
    Queue patients;
    patients.add_to_end("Jack");
    patients.print();
    patients.add_to_end("Jill");
    patients.print();
    patients.add_to_end("Ann");
    patients.print();
    patients.add_to_end("Bill");
    patients.print();

    patients.remove("Ann");
    patients.print();
    patients.remove("Bill");
    patients.print();
    patients.remove("Jack");
    patients.print();
    patients.remove("Jill");
    patients.print();
    cout<<"Bye!"<<endl;
    return 0;
}
