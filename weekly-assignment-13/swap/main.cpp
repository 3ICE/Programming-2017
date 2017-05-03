#include<iostream>
#include<string>

using namespace std;

template<typename T>
void swap2(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

struct Example{
    string m;
};

//3ICE: For printing Example objects
ostream &operator<<(ostream& os, Example& e) {
    return os<<e.m;
}

int main() {
    int a = 0;
    int b = 3;
    cout<<a<<"  "<<b<<endl;
    swap2(a, b);
    cout<<a<<"  "<<b<<endl<<endl;

    string c = "Hello";
    string d = "there!";
    cout<<c<<"  "<<d<<endl;
    swap2(c, d);
    cout<<c<<"  "<<d<<endl<<endl;

    Example e; e.m="this_Example_object";
    Example f; f.m="THAT_Example_object";
    cout<<e<<"  "<<f<<endl;
    swap2(e, f);
    cout<<e<<"  "<<f<<endl<<endl;
}
