#ifndef QUEUE_H
#define QUEUE_H
//3ICE: From weekly-assignment-10

#include <string>

using namespace std;

class Queue {
public:
    Queue();
    ~Queue();
    bool empty() const;
    void push_back(const string& name);
    bool pop_front(string& name);
    bool erase(int id);
    int print(int continue_from) const;
    int count() const;

private:
    struct Cell {
        string name;
        Cell *nxt;
    };

    Cell *fst;
    Cell *lst;
};

#endif
