#include <iostream>

using namespace std;

//3ICE: Weekly exercise #10
//3ICE: but implemented using a dynamic array instead of a linked list
//3ICE: Now further improved with templates!
//3ICE: And finally for project-03 I added more documentation.
//3ICE: And lengthened variable names, and limited to 80 characters per line
//3ICE: And new functions such as erase. And changed how print works.
template <typename TYPE>
class Stack {
private:
    TYPE* array; //a
    int max_size; //m

public:
    Stack():max_size(0){}

    ~Stack(){
        delete [] array;
        max_size = 0;
        array = nullptr;
    }

    void init(int size) {
        //cout<<"NOTICE: Stack was resized from m="<<max_size;
        max_size = size;
        //cout<<" to "<<max_size<<endl;
        delete[] array;
        array = new TYPE[max_size];

        //If there was an earlier list, it is destroyed and a new one is
        //initialized from scratch (unless an error condition is met)
        //copy(array, array+current_size, new_array);
        //3ICE: Instead of the above magic, we could:
        //for(int i=0;i<n;++i) {
        //    b[i] = a[i];
        //}
    }

    int size() const{
        return max_size;
    }

    //3ICE: Array-like indexing for convenience:
    TYPE operator[](int idx){
        if(idx >= max_size){
            throw out_of_range("too large index");
        }
        return array[idx];
    }

    void print() const{
        int i = max_size;
        int continue_from = 1;
        while(i > 1){
            if(!array[i--].empty()){
                cout << "Priority level " << i + 1 << ":"<<endl;
                continue_from = array[i].print(continue_from);
            }
        }
    }

    bool erase(int id){
        int i = max_size;
        int count = 1;
        while(i > 1 && id < count){
            count += array[i--].count();
        }
        return array[i++].erase(count-id);
    }
};

//3ICE: template has to be repeated for functions declared outside, like this:
//template <typename T>
//void Stack<T>::do_nothing() const {}
