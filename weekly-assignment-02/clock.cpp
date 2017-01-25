#include <iostream>
#include <iomanip>

using namespace std;


class Clock {
  public:
    Clock(int hour, int minute);
    void tick_tock();
    void print() const;

  private:
    int hours_;
    int minutes_;
};


int main() {
    Clock time(23, 59);
    time.print();
    time.tick_tock();
    time.print();
}


Clock::Clock(int hour, int minute):
    hours_(hour), minutes_(minute) {
}


void Clock::tick_tock() {
    ++minutes_;
    if ( minutes_ >= 60 ) {
        minutes_ = 0;
        ++hours_;
    }

    if ( hours_ >= 24 ) {
        hours_ = 0;
    }
}


void Clock::print() const {
    cout << setw(2) << setfill('0') << hours_
         << "."
         << setw(2) << minutes_
         << endl;
}
