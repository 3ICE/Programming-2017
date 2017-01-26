#include <iostream>
#include <iomanip>

using namespace std;


class Clock {
public:
    Clock(int hour, int minute);
    void print() const;
    int difference(Clock o);

private:
    int hours_;
    int minutes_;
};


int main() {
    int min, hour;
    cout<<"Please type in an hour: ";
    cin>>hour;
    cout<<"Please type in a minute: ";
    cin>>min;
    Clock one(hour, min);
    cout<<"You entered: "; one.print();
    cout<<endl<<"Please type in another hour: ";
    cin>>hour;
    cout<<"Please type in another minute: ";
    cin>>min;
    Clock two(hour, min);
    cout<<"You entered: "; two.print();
    cout<<endl<<"Difference will be calculated between: "<<endl;
    one.print(); cout<<" and "; two.print();
    cout<<endl<<"Calculating..."<<endl;
    cout<<endl<<"And the results are in:"<<endl<<endl;
    cout << one.difference(two) << endl<< endl;
    //Clock.difference(one,two);
}


Clock::Clock(int hour, int minute):
    hours_(hour), minutes_(minute) {
}


int Clock::difference(Clock o) {
    //3ICE: 23.55 - 00.05 -> 10 makes no sense :(
    //3ICE: I'd much rather take the absolute value
    //3ICE:  of their difference! Oh well...
    int x=hours_*60+minutes_ - o.hours_*60-o.minutes_;
    if(x<0){return -x;}else{return 1440-x;}
}

void Clock::print() const {
    cout << setw(2) << setfill('0') << hours_<< ":"<< setw(2) << minutes_;
}
