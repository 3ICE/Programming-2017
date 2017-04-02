#ifndef QUEUE_HH
#define QUEUE_HH

#include <string>

using namespace std;

class Queue {
  public:
    Queue();

    // Add new patient to the end of the service queue.
    void add_to_end(const string& new_patient_name);

    // Remove the patient who has been waiting the longest
    // i.e. the patient in the fromt of the queue.
    bool remove_from_front(string& removed_patient_name);

    // Is there any patients waiting.
    bool is_empty() const;

    // Print the patients currently waiting in queue.
    void print() const;

    ~Queue();

  private:
    struct Cell {
        string patient_name;
        Cell *next_ptr;
    };

    // Pointer to the first element of the linked list.
    Cell* first_ptr_;

    // Pointer to the last element of the linked list.
    Cell* last_ptr_;
};

#endif
