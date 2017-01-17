#include <iostream>

using namespace std;

int abs(int i){
    if(i<0) return -i;
    return i;
}


int main(/*int argc, char *argv[]*/){
    cout << "Hello! Type a number please..." << endl;
    int i = 0;
    cin >> i;
    if (i>=0) {
        cout << "You entered a positive number: " << i << endl;
    } else {
        cout << "You entered a negative number: " << abs(i) << endl;
    }

    return 0;
}
