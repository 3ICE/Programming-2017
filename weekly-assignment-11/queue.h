#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

class Queue {
public:
    Queue();
    ~Queue();

    void add_to_end(const string& new_patient_name);
    bool remove(const string& patient_name);
    void print() const;

private:
    struct Cell {
        string name;
        Cell *nxt;
    };

    Cell *fst;
    Cell *lst;
};

#endif
