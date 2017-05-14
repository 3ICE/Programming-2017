/** This file used to be an automated test for my stack implementation.
 * Until it got completely destroyed by all the new changes.
 * Kept as reference / memorabilia. To remember... Back when it was simple...
 * Mostly commented out now. Does nothing whatsoever. Interesting read though.
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "stack.hh"
#include <iostream>

using namespace std;

struct Example{
    string message;
    int id;
};

//3ICE: For printing Example objects
ostream &operator<<(ostream& os, Example& e) {
    return os<<"{"<<e.message<<" "<<e.id<<"}";
}

//3ICE: Notice: All .print()s and cout<<s are commented out in project-03
//because of the automated tester. + I deleted the entire test_queue.cpp file
void test_stack(){
    //cout<<"Hello!"<<endl;
    //cout<<"Creating a dynamic stack, s"<<endl;
    Stack<int> test_stack_1; //s
//    if(test_stack_1.empty()){
//        cout<< "Yes, stack s is empty."<<endl;
//    }
    //test_stack_1.push_back(3);
    //cout<<"Added one element to s, my favorite number (3). Here it is:";
    //s.print();
//    if(!test_stack_1.empty()){
//        cout<< "And the stack is no longer empty."<<endl;
//    }
    //int x;
    //test_stack_1.pop_front(x);
    //cout<<"Removed element "<<x<<" from stack s."<<endl;
//    if(test_stack_1.empty()){
//        cout<< "And stack s is empty again... So, let's fill it up!"<<endl;
//    }
//    for (int i = 0; i <= 10; ++i) {
//        test_stack_1.push_back(i);
//        s.print();
//    }
    //cout<<"All numbers were successfully 0-10 pushed into stack s."<<endl;
    //cout<<"Now I want that in reverse! Luckily we can flip it easily."<<endl;
    //cout<<"Gotta use two stacks for this... Creating a second stack, t";
    Stack<int> test_stack_2; //t
//    if(test_stack_2.empty()){
//        cout<< "Of course, stack t is empty to begin with."<<endl;
//    }
    //cout<<"All elements popped from stack s, pushed to stack t, one by one:";
    for(int i = 0; i <= 10; ++i){
        //test_stack_1.pop_front(x);
        //test_stack_2.push_back(x);
        //s.print();
        //t.print();
    }
    //cout<<"Numbers 10-0 (reversed) are stored in stack t now."<<endl;
//    if(test_stack_1.empty()){
//        cout<< "And finally, stack s is of course empty again,"
//        <<" since we popped everything it had."<<endl;
//    }

    Stack<int>* testing_delete= new Stack<int>;
//    testing_delete->push_back(1);
//    testing_delete->push_back(2);
//    testing_delete->push_back(3);
    delete testing_delete;
    //cout << "p.s.: Deleting works too, by the way."
    //<<" (If this line is printed.)" << endl;

    //cout << "Another example, a stack of Example objects:" << endl;
    //Stack<Example> example_stack; //e
    //e.print();
    for(int i = 1; i < 4; ++i){
        Example tmp; //x
        tmp.message="Example object";
        tmp.id=i;
        //example_stack.push_back(tmp);
        //cout<<"pushed: "<<x<<": ";
        //e.print();
    }
    //    while(not example_stack.empty()){
    //        Example x;
    //        example_stack.pop_front(x);
    //        cout<<"popped: "<<x<<": ";
    //        e.print();
    //    }

    //cout << "Bye!" << endl;
}
