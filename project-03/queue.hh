/** This file is a linked list implementation. I declare my function signatures
 * here, and implement them in queue.cpp as any good student would do.
 * Justification for the perhaps overly short variable names fst, lst, and nxt:
 * That is the standard naming convention in Haskell and many other languages.
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#ifndef QUEUE_H
#define QUEUE_H
//3ICE: From weekly-assignment-10

#include <string>

using namespace std;

//3ICE: Class Queue implements a standard queue using a singly linked list with
//3ICE: pointers at both ends to simplify pushing back and popping front (FIFO)
//3ICE: Retrospect: I really regret using a linked list. Also "size" would have
//3ICE: been a useful property to add, and keep track of. Instead of counting.
class Queue {
public:
    //3ICE: Standard ctor and dtor:
    Queue();
    ~Queue();

    //3ICE: Standard queue relevant functions
    bool empty() const;
    void push_back(const string& name);
    bool pop_front(string& name);
    int count() const;

    //3ICE: These function are specifically adapted to the various requirements
    bool erase(int id);
    int print(int continue_from) const;

private:
    //3ICE: Standard Node inner struct/class with a string and a next pointer.
    //3ICE: (named Cell because of its translation from Finnish)
    struct Cell {
        string name;
        Cell *nxt;
    };

    //3ICE: Standard head/first pointer and a bonus pointer to the last item.
    Cell *fst;
    Cell *lst;
};

#endif
