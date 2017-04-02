#include <iostream>

using namespace std;

//It is probably a good idea to implement Stack as a module,
//like the example from the lecture was done.
//3ICE: No thanks :)
class Stack {
private:
    struct Cell {
        int data;
        Cell* next_ptr;
    };

    Cell* first_ptr;

public:
    //3ICE: Totally not required, default constructor does the same.
    Stack():first_ptr{nullptr}{}

    //3ICE: Destroy each Cell, deconstructing the chain link by link.
    ~Stack(){
        Cell* p = first_ptr;

        while (p != nullptr){
            Cell* q = p->next_ptr;
            delete p;
            p = q;
        }

        first_ptr = nullptr;
    }

    // empty will only return true, if there are no elements
    // in the stack i.e. the linked  list is empty.
    bool empty() const{
        return first_ptr==nullptr;
    }

    // push_front will insert the new_value on top of the stack
    // i.e. in front of the linked list.
    void push_front(int new_value){
        Cell* c = new Cell;
        c->data=new_value;
        c->next_ptr=first_ptr;
        first_ptr=c;
    }


    // pop_front will remove the topmost value from the stack
    // i.e. the first element of the linked list.  The removed
    // value will be stored into removed_value and the return
    // value will be true if the removal of an element is successfull.
    // If not (i.e. the stack is empty), return value is false.
    bool pop_front(int& removed_value){
        Cell* t = first_ptr;
        first_ptr= first_ptr->next_ptr;
        removed_value=t->data;
        delete t;
        return !this->empty();
    }

    // Print the elements stored in the stack on top to bottom
    // order.  This method is mainly for testing purposes.
    void print() const{
        Cell* p = first_ptr;

        while (p != nullptr){
            cout << p->data << " ";
            p = p->next_ptr;
        }

        cout<<endl;
    }
};

//Of course you also need to implement some sort of
//main function to be able to test your Stack class.
int main(){
    cout<<"Hello!"<<endl;
    cout<<"Creating a stack, s"<<endl;
    Stack s;
    if(s.empty()) cout<< "Yes, stack s is empty."<<endl;
    s.push_front(3);
    cout<<"Added one element to s, my favorite number (3). Here it is:"<<endl;
    s.print();
    if(!s.empty()) cout<< "And the stack is no longer empty."<<endl;
    int x;
    s.pop_front(x);
    cout<<"Removed element "<<x<<" from stack s."<<endl;
    if(s.empty()) cout<< "And stack s is empty again... So, let's fill it up!"<<endl;
    for (int i = 0; i <= 10; ++i) {
        s.push_front(i);
    }
    cout<<"All numbers 0-10 pushed into stack s. Here they are:"<<endl;
    s.print();
    cout<<"Oops, that's in reverse! Luckily we can flip it easily."<<endl;
    cout<<"Gotta use two stacks for this... Creating a second stack, t"<<endl;
    Stack t;
    if(t.empty()) cout<< "Of course, stack t is empty to begin with."<<endl;
    cout<<"All elements popped from stack s, pushed to stack t, one by one."<<endl;
    for (int i = 0; i <= 10; ++i) {
        s.pop_front(x);
        t.push_front(x);
    }
    cout<<"Numbers 0-10 are stored in stack t now. Printing reversed:"<<endl;
    t.print();
    if(s.empty()) cout<< "And finally, stack s is of course empty again, since we popped everything it had."<<endl;
    cout << "Bye!" << endl;

    Stack* testing_delete= new Stack;
    testing_delete->push_front(1);testing_delete->push_front(2);testing_delete->push_front(3);
    testing_delete->print();
    delete testing_delete;
    cout << "p.s.: Deleting works too, by the way. (If this line is printed.)" << endl;

    return 0;
}
