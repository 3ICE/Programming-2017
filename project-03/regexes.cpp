#include<iostream>
#include<iomanip>
#include<string>
#include<regex>

using namespace std;

void regex_example() {
    //3ICE: Ignores leading and trailing spaces as well (no trim necessary)
    regex reg("\\ *([0-9]{1,2})\\.([0-9]{1,2})\\.([0-9]{4})\\ *");
    smatch res;
    cout<<"(CTRL+C to quit) Input dates in the following format: dd.mm.yyyy"<<endl;
    string line;
    while(getline(cin, line)){
        if(regex_match(line, res, reg)){
            string d = res.str(1);
            string m = res.str(2);
            string y = res.str(3);
            cout<<setfill('0')<<y<<"-"<<setw(2)<<m<<"-"<<setw(2)<<d<<endl<<endl;
        } else cout<<"Not a recognized date!"<<endl;
    }
}

//3ICE: Sample run:
//(CTRL+C to quit) Input dates in the following format: dd.mm.yyyy
//1.2.2017
//2017-02-01

//01.2.2017
//2017-02-01

//1.02.2017
//2017-02-01

//01.02.2017
//2017-02-01

//    01.02.2017
//2017-02-01

//2017.02.01.
//Not a recognized date!

//3ICE: Validating dates was not part of the scope, so these also work:
//1.1.1111
//1111-01-01

//0.0.0000
//0000-00-00

//2.2.2222
//2222-02-02

//9.9.9999
//9999-09-09

//99.99.9999
//9999-99-99
