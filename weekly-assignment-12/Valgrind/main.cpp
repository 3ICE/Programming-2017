#include <iostream>

using namespace std;

int main() {
    int number1 = 111;
    int number2 = 222;
    int *pointer1 = new int(333);
    int *pointer2 = new int(444);

    cout << number1 << " "
         << number2 << " "
         << *pointer1 << " "
         << *pointer2 << endl;

    delete pointer1;
    delete pointer2;
}
