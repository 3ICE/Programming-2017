#include <iostream>
#include <string>
using namespace std;

int main(/*int argc, char *argv[]*/)
{
    string secret_word="BUDAPEST";
    int lives=5;
    int correct_guesses=0;
    while(lives>=0) {
        cout<<"Enter a letter ";
        char x;
        cin>>x;
        if(secret_word.find(x)!=string::npos){
            cout<<"correct guess"<<endl;
            correct_guesses=correct_guesses+1;
            if(correct_guesses==8){
                cout<<"you win"<<endl<<endl;
                break;
            }

        } else {
            cout<<"incorrect guess"<<endl;
            lives=lives-1;
            cout<<"You have "<<lives<<" lives left"<<endl;
        }
    }
    cout << "Game Over" << endl;
    return 0;
}
