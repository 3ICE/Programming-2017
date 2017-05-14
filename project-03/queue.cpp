/** This file is a linked list implementation. I hate implementing linked lists
 * by hand. Especialy tough was the part about erasing by "running number" id.
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "queue.hh"
#include <iostream>
#include <string>

using namespace std;

//3ICE: "Constructor?" "Yes, hello, this is Constructor."
Queue::Queue(): fst(nullptr), lst(nullptr){}

//3ICE: Had issues with destructor randomly being called on objects I still
//3ICE: needed. Out of scope problem or something. I messed up operator[] bad.
Queue::~Queue(){
    //cout<<"deleting queue:"<<endl;
    Cell* p;
    while(fst != nullptr){
        p = fst;
        fst = fst->nxt;
        //cout<<" deleting item "<<p->name<<endl;
        delete p;
    }
}

// empty will only return true, if there are no elements
// in the queue i.e. the linked list is empty.
bool Queue::empty() const{
    return fst == nullptr;
}

//3ICE: Specialized print function with the fancy two spaces in front.
int Queue::print(int continue_from) const {
    Cell* p = fst;

    while(p != nullptr){
        cout << "  " << continue_from << ". " << p->name << endl;
        ++continue_from;
        p = p->nxt;
    }
    return continue_from;
}

//3ICE: Point of inefficiency (Have to recount each time we erase)
int Queue::count() const {
    Cell* p = fst;
    int counter = 0;
    while(p != nullptr){
        ++counter;
        p = p->nxt;
    }
    return counter;
}


//3ICE: Standard push_back method, I think.
void Queue::push_back(const string& name){
    Cell* p(new Cell);

    p->name = name;
    p->nxt = nullptr;

    if(fst == nullptr){
        fst = p;
        lst = p;
    } else {
        lst->nxt = p;
        lst = p;
    }
}

//3ICE: Standard pop_front as well.
bool Queue::pop_front(string& name) {
    if(empty()){
        return false;
    }

    Cell *p = fst;

    name = p->name;

    if(fst == lst){
        fst = nullptr;
        lst = nullptr;
    } else {
        fst = fst->nxt;
    }

    delete p;
    return true;
}

//3ICE: Now this erase is anything but standard. And is done in two steps.
//3ICE: Number of debug prints directly correlates to how much trouble I had
//with this function. Especially that OOPS! - I was erasing from the wrong list
bool Queue::erase(int id){
    //cout<<"  Deleting #"<<id<<endl;
    if(fst == nullptr || id < 0){
        return false;
    }
    if(id == 0){
        //cout<<"   Deleting first is special case"<<endl;
        Cell* p = fst;

        if(fst == lst){
            fst = nullptr;
            lst = nullptr;
        } else {
            fst = fst->nxt;
        }

        delete p;
        return true;
    }
    //cout<<"   Fast forwarding to #"<<id-1<<endl;
    Cell* p = fst;
    int counter = 1;
    //cout<<p<<" "<<p->name<<" "<<p->nxt<<endl;
    //cout<<counter <<" "<< id<<endl;
    while(counter < id){
        //cout<<p<<" "<<p->name<<" "<<p->nxt<<endl;
        if(p == lst){
            //cout<<"  OOPS!"<<endl;
            return false;
        }
        p = p->nxt;
        ++counter;
        //cout<<"  "<<counter<<" "<<p->name<<endl;
    }

    // Here p points to the cell that is right in front of the id'th element.

    Cell* q = p->nxt;
    p->nxt = q->nxt;

    if(lst == q){
        //cout<<"   Deleting last is special case, so updated lst"<<endl;
        lst = p;
    }

    //cout<<"   Deleting #"<<id<<": "<<q->name<<endl;
    delete q;
    return true;
}
