#include <iostream>

using namespace std;

//3ICE: #10, but implemented using a dynamic array instead of a linked list
class Stack {
private:
    int* a; // array
    int  m; // max size
    int  n; // now (size)

public:
    //3ICE: Why initialize with size 3? Just because 3 is my favorite number :)
    Stack():a(new int[3]), m(3), n(0){}

    ~Stack(){
        delete [] a;
        n = 0;
        m = 0;
        a = nullptr;
    }

    bool empty() const{
        return n==0;
    }

    //3ICE: The example solution has a mistake here (push_front pushes to back, actually)
    //3ICE: but instead of fixing it I just renamed the method to:
    void push_back(int v){
        if (m > n) a[n++] = v;
        else {
            //3ICE: Have to resize.
            cout<<"NOTICE: Stack was resized from m="<<m;
            m *= 2;
            cout<<" to "<<m<<endl;
            int* b = new int[m];
            copy(a, a+n, b);
            //3ICE: Instead of the above magic, we could:
            //for(int i=0;i<n;++i) {
            //    b[i] = a[i];
            //}

            delete[] a;
            a = b;

            //3ICE: Remember to add the value as well!
            a[n++] = v;
            //++n would yield: 0 1 2 0 4 5 0 7 8 9 10
        }
    }

    bool pop_front(int& v){
        if(n == 0) return false;
        v = a[--n];
        //--n would yield: 0 10 9 8 7 6 5 4 3 2 1
        return true;
    }

    void print() const{
        int i = 0;
        while(i < n) cout << a[i++] << " ";
        cout << endl;
    }
};

int main(){
    cout<<"Hello!"<<endl;
    cout<<"Creating a dynamic stack, s"<<endl;
    Stack s;
    if(s.empty()) cout<< "Yes, stack s is empty."<<endl;
    s.push_back(3);
    cout<<"Added one element to s, my favorite number (3). Here it is:"<<endl;
    s.print();
    if(!s.empty()) cout<< "And the stack is no longer empty."<<endl;
    int x;
    s.pop_front(x);
    cout<<"Removed element "<<x<<" from stack s."<<endl;
    if(s.empty()) cout<< "And stack s is empty again... So, let's fill it up!"<<endl;
    for (int i = 0; i <= 10; ++i) {
        s.push_back(i);
        s.print();
    }
    cout<<"All numbers were successfully 0-10 pushed into stack s."<<endl;
    cout<<"Now I want that in reverse! Luckily we can flip it easily."<<endl;
    cout<<"Gotta use two stacks for this... Creating a second stack, t"<<endl;
    Stack t;
    if(t.empty()) cout<< "Of course, stack t is empty to begin with."<<endl;
    cout<<"All elements popped from stack s, pushed to stack t, one by one:"<<endl;
    for (int i = 0; i <= 10; ++i) {
        s.pop_front(x);
        t.push_back(x);
        s.print();
        t.print();
    }
    cout<<"Numbers 10-0 (reversed) are stored in stack t now."<<endl;
    if(s.empty()) cout<< "And finally, stack s is of course empty again, since we popped everything it had."<<endl;
    cout << "Bye!" << endl;

    Stack* testing_delete= new Stack;
    testing_delete->push_back(1);testing_delete->push_back(2);testing_delete->push_back(3);
    delete testing_delete;
    cout << "p.s.: Deleting works too, by the way. (If this line is printed.)" << endl;

    return 0;
}
