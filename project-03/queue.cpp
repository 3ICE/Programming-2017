#include "queue.hh"
#include <iostream>
#include <string>

using namespace std;

Queue::Queue(): fst(nullptr), lst(nullptr){}

Queue::~Queue(){
    Cell* p;
    while(fst != nullptr){
        p = fst;
        fst = fst->nxt;

        delete p;
    }
}

// empty will only return true, if there are no elements
// in the queue i.e. the linked list is empty.
bool Queue::empty() const{
    return fst == nullptr;
}

int Queue::print(int continue_from) const {
    Cell* p = fst;

    while(p != nullptr){
        cout <<" " << continue_from << ". " << p->name << endl;
        ++continue_from;
        p = p->nxt;
    }
    return continue_from;
}

int Queue::count() const {
    Cell* p = fst;
    int counter = 0;
    while(p != nullptr){
        ++counter;
        p = p->nxt;
    }
    return counter;
}

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

bool Queue::erase(int id){
    if(fst == nullptr){
        return false;
    }
    if(id == 0){
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

    Cell* p = fst;
    int counter = 0;
    while(counter < id){
        if(p == lst){
            return false;
        }
        p = p->nxt;
        ++counter;
    }

    // Here p points to the cell that is right in front of the id'th element.

    Cell* q = p->nxt;
    p->nxt = q->nxt;

    if(lst == q){
        lst = p;
    }

    delete q;
    return true;
}
