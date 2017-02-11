#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Clock{
public:
    Clock(int hour, int minute);
    void print()const;
    int fetch_hour()const;
    int fetch_minutes()const;
    bool operator<(const Clock& b);

private:
    int m_;
};

int main(){
    vector<Clock> times = {};
    int total, hour, min;
    cout<<"3ICE: How many times will you enter? ";
    cin>>total;
    for(int i = 1; i <= total; ++i) {
        cout << "3ICE: Enter hour for clock " << i << ": "; cin >> hour;
        cout << "3ICE: Enter minutes for clock " << i << ": "; cin >> min;
        times.push_back(Clock(hour,min));
    }
    cout<<endl<<"3ICE: You entered the following times:"<<endl;
    for(int i = 0; i < total; ++i) times[i].print();

    cout<<endl<<"3ICE: Here they are, sorted in ascending order:" << endl;

    sort(times.begin(),times.end()); //3ICE: Uses Clock::operator< by default

    for(int i = 0; i < total; ++i) times[i].print();
}

bool Clock::operator<(const Clock&b){return this->m_ < b.m_;}
Clock::Clock(int hour, int minute):m_(60 * hour + minute){}
int Clock::fetch_hour()const{return m_ / 60;}
int Clock::fetch_minutes()const{return m_ % 60;}
void Clock::print()const{
    cout << setfill('0')<< setw(2)<< fetch_hour()
         << ":"<< setw(2)<< fetch_minutes()<< endl;
}
