/** This file is a stack implementation squeezed in just the header file.
 * No cpp - I do demonstrate my ability to work with cpp+hh file pairs in past
 * projects and also in queue.hh + queue.cpp found in this project, here.
 * This file would be a grand total of 40 lines long, without all the comments
 * Yeah! This file is 30% code, 70% comments and blank lines. I overdid it :)
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "queue.hh"
#include <iostream>

using namespace std;

//3ICE: Weekly exercise #10
//3ICE: but implemented using a dynamic array instead of a linked list
//3ICE: Now further improved with templates!
//3ICE: And finally for project-03 I added more documentation.
//3ICE: And lengthened variable names, and limited to 80 characters per line
//3ICE: And introduced new functions such as erase.
//3ICE: And changed how print works. And got confused with simple arithmetic.
template <typename TYPE>
class Stack {
private:
    TYPE* array; //a
    int max_size; //m

public:
    //Initialized with [1] just so we have something to delete. Feels bad man.
    Stack():array(new TYPE[1]),max_size(0){}

    //3ICE: Required because "All the dynamic memory your program allocates
    //3ICE: with new must be released with delete __before__ the program ends."
    ~Stack(){
        delete [] array;
        max_size = 0;
        array = nullptr;
    }

    //3ICE: Used to be a bigger resize function for copying over the values.
    //3ICE: Now just deletes everything and makes a new array as required.
    void init(int size) {
        //cout<<"NOTICE: Stack was resized from m="<<max_size;
        max_size = size;
        //cout<<" to "<<max_size<<endl;
        delete[] array;
        array = new TYPE[max_size];
        //for(int i=0; i<max_size; ++i){
        //    array[i].push_back("33");
        //}

        //If there was an earlier list, it is destroyed and a new one is
        //initialized from scratch (making the following code obsolete)
        //copy(array, array+current_size, new_array);
        //3ICE: Instead of the above magic, we could:
        //for(int i=0;i<n;++i) {
        //    b[i] = a[i];
        //}
    }

    //3ICE: Used to return current_size, but that was done away with as well.
    int size() const{
        return max_size;
    }

    //3ICE: Array-like indexing for convenience. Not used in the end.
    TYPE operator[](int idx){
        if(idx >= max_size){
            throw out_of_range("too large index");
        }
        return array[idx];
    }

    //3ICE: Exposes the underlying queue's push_back function to top level
    //callers. Replaces the above operator[], is more reliable.
    void push_back(int priority, string name){
        //3ICE: Could catch index out of bounds errors here but decided against
        array[priority-1].push_back(name);
    }

    //3ICE: Specialized print function with the fancy priority level in front.
    //3ICE: Also keeps track of a running index because it was required to do.
    void print() const{
        int i = max_size;
        int continue_from = 1;
        while(i > 0){
            --i;
            if(!array[i].empty()){
                cout << "Priority level " << i + 1 << ":"<<endl;
                continue_from = array[i].print(continue_from);
            }//else{cout<<i;}
        }
    }

    //3ICE: Reconstructs the above introduced running index, but differently.
    //3ICE: Then calls the erase function at the correct array index and with
    //3ICE: the (hopefully!) right offset. Took me hours... Trial and error.
    bool erase(int id){
        //3ICE: If you look at all the debug prints you can almost feel my
        //frustration. Almost. And this is only half of it :)
        //cout<<"erasing "<<id<<endl;
        int i = max_size;
        int count = 1;
        while(i > 0 && id >= count){
            --i;
            //cout<<" i is "<<i<<", count is "<<count<<endl;
            count += array[i].count();
            //cout<<" at "<<i<<", skipped "<<count<<endl;
        }
        //3ICE: While loop exited either because we reached the lowest priority
        //3ICE: Or we jumped over the priority that held our desired item.
        //3ICE: Either way, we go back one and delete the count-id'th element.
        //cout<<" STOP: i is "<<i<<", "<<count<<" is off by "<<count-id<<endl;
        //cout<<"erased ["<<i<<"] ("<<count-(count-id)-1<<")"<<endl;
        //3ICE: I am so confused by this math! -- brute forced my way to this:
        return array[i].erase(count-(count-id)-1);
    }

    //3ICE: Exposes the underlying queue's empty function to top level callers.
    bool empty(int id){
        return array[id].empty();
    }

    //3ICE: Exposes the underlying queue's pop_front function to top level.
    void pop_front(int priority, string& name){
        array[priority].pop_front(name);
    }
};

//3ICE: template has to be repeated for functions declared outside, like this:
//template <typename T>
//void Stack<T>::do_nothing() const {}
//3ICE: Didn't need to do this at all, since ths class is no longer generic --
//3ICE: Only works with this specific Queue class as it expects print to return
//3ICE: an int, etc. (That behavior is not standard.)
