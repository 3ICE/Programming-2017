// The purpose on this example is to demonstrate
// how the private part of a class can be comletely
// redesigned hwile the public interface stays the same.
// Although, two methods fetch_hour and fetch_minutes
// were added to the public interface, but they are
// unrelated to the fact that the original three
// methods are the same.

#include <iostream>
#include <iomanip>

using namespace std;


class Clock {
  public:
    Clock(int hour, int minute);
    void tick_tock();
    void print() const;

    int fetch_hour() const;
    int fetch_minutes() const;

  private:
    // Minutes since the previous midnight.
    int minutes_since_midnight_;
};


int main() {
    Clock time(23, 59);
    time.print();
    time.tick_tock();
    time.print();
}


Clock::Clock(int hour, int minute):
    minutes_since_midnight_(60 * hour + minute) {
}


void Clock::tick_tock() {
    ++minutes_since_midnight_;

    if ( minutes_since_midnight_ >= 24 * 60 ) {
        minutes_since_midnight_ = 0;
    }
}


int Clock::fetch_hour() const {
    // When you divide an integer by an integer
    // the result is a rounded down integer.
    return minutes_since_midnight_ / 60;
}


int Clock::fetch_minutes() const {
    return minutes_since_midnight_ % 60;
}


void Clock::print() const {
    // Notice how print-method doesn't need to know what
    // variables are hidden in the private section of the class.
    // It utilizes the helper methods fetch_hour and fetch_minutes
    // to figure out the time.  The good point of this is that
    // if we change the implementation (private part) of the class
    // print-method can stay the same.

    cout << setfill('0') << setw(2) << fetch_hour()
         << "."
         << setw(2) << fetch_minutes()
         << endl;
}
