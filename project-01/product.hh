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
#ifndef PRODUCT_HH
#define PRODUCT_HH
//3ICE: There must be at least one class in your program.

#include <string>
#include <iostream>
#include <iomanip>

class product{
public:
    product(std::string name, double price){
        this->name=name;
        this->price=price;
    }
    /**
     * @brief product::operator < compares two objects by their price.
     * @param b the other product object
     * @return super() comparator (price)
     */
    bool operator<(const product&b);

    /**
     * @brief product::print does what is expected. The only trickery is
     * that the price will be printed with exactly two decimals as is
     * customary with dollar amounts.
     */
    void print();
    std::string name; //3ICE: Not bothering with private
    double price; //3ICE: Getter setter is nothing but spam anyway.
};
#endif // PRODUCT_HH
