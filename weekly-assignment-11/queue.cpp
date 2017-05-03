#include "queue.h"
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

void Queue::print()const {
    Cell* p = fst;
    int i = 1;

    while(p != nullptr){
        cout << i << ": " << p->name << endl;
        ++i;
        p = p->nxt;
    }
    cout<<endl;
}

void Queue::add_to_end(const string& name){
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

bool Queue::remove(const string& name){
    if(fst == nullptr) return false;
    if(fst->name == name){
        Cell* p = fst;

        if(fst == lst){
            fst = nullptr;
            lst = nullptr;
        } else fst = fst->nxt;

        delete p;
        return true;
    }

    Cell* p = fst;
    while(true){
        if(p == lst)return false;
        if(p->nxt->name == name){
            break;
        } else {
            p = p->nxt;
        }
    }

    // Here p points to the cell that is right in front of the element to be removed.

    Cell* q = p->nxt;
    p->nxt = q->nxt;

    if(lst->name == name){
        lst = p;
    }

    delete q;
    return true;
}
