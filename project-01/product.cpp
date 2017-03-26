/** product.hh houses a relatively simple struct.
 * Support for printing, and comparing is present.
 * The housed object has a name and a price, both
 * are publicly available for modification at any
 * time and from any part of the code.
 *
 * @question: Why do header files have the extension
 * .hh in Finland? Everywhere else I've studied
 * it's always been just .h for headers. (or .hpp)
 *
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "product.hh"
using namespace std;

/**
 * @brief product::operator < compares two objects by their price.
 * @param b the other product object
 * @return super() comparator (price)
 */
bool product::operator<(const product&b){
    return this->price < b.price;
}

/**
 * @brief product::print does what is expected. The only trickery is
 * that the price will be printed with exactly two decimals as is
 * customary with dollar amounts.
 */
void product::print(){
    cout << name << " " << setprecision(2) << fixed << price << endl;
}
