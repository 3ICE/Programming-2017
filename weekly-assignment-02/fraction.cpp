/*
  Yes, I intentionally made this as unreadable as possible.
  Do you like it? Spaghetti code / alphabet soup code :)
  --Daniel "3ICE" Berzvai
*/
#include <iostream>
using namespace std;
class F{
public:
    F(int n=0,int d=0); //3ICE: constructor
    F m(F o); //3ICE: multiply
    F d(F o); //3ICE: divide
    F a(F o); //3ICE: add
    F s(F o); //3ICE: subtract
    F i()const; //3ICE: inverse
    F n()const; //3ICE: negate
    void p()const; //3ICE: print

    void setN(int n); //3ICE: setter for numerator
    void setD(int d); //3ICE: setter for denominator
    //int n()const;
    //int d()const; //3ICE: getters not needed

private:
    int n_,d_;
};

F::F(int n,int d):n_(n),d_(d){}
F F::m(F o){return F(n_*o.n_,d_*o.d_);} //3ICE: multiply
F F::d(F o){return m(o.i());} //3ICE: divide
F F::a(F o){return F(n_*o.d_+d_*o.n_,d_*o.d_);} //3ICE: add
F F::s(F o){return a(o.n());} //3ICE: subtract
F F::i()const{return {d_,n_};} //3ICE: inverse
F F::n()const{return {-n_,d_};} //3ICE: negate
void F::p() const{cout<<n_<<"/"<<d_<<endl;}//3ICE: print

void F::setN(int n){n_ = n;}
void F::setD(int d){d_ = d;}
//int F::n()const{return n_;}
//int F::d()const{return d_;}

int main(/*int argc,char *argv[]*/){
    F(4,5)
            .s(F(5,8))
            .a(F(1,8))
            .d(F(2,3)
               .m(F(1,7)))
            .p();

    F f(1,-2);
    f.p();

    F g;
    g.setN(-4);
    g.setD(-7);
    g.p();

    f.m(g).p();
    f.d(g).p();

    int n=0;
    cout<<"Enter numerator: ";
    cin>>n;
    int d=0;
    cout<<"Enter denominator: ";
    cin>>d;
    F h(n,d);
    h.p();


    return 0;
}
/**Use C++ to implement a class Fractional you can use to
 * make arithemetic calculations using fractional numbers
 * (i.e. ?, ?, and so on)
 * After you finish implementing your Fractional class
 * use it to calculate and print the value for the expression:
 * Before you start coding give some thought to the
 * public interface of the class.
*/
