/** My data structure for holding marketplaces of stores of products, with
 * their name+price. Consists of a map, which in turn holds maps of vectors.
 * The ->first of each map is the market / store name, the -> second is the
 * contents. I could have used map of map of map, but wanted two different
 * STL containers. Oh well, only indexing will be slightly harder... (For
 * example database[market][store][product] vs database[market][store] and
 * then messing with the vector inside, indexed with integers, not by name.)
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#ifndef DATA_HH
#define DATA_HH
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include "product.hh"
#include "splitter.hh"

/** Data structure or Data base, call it what you want. Holds a 4D matrix of
 * information. (markets, stores, products with names, prices)
 * @note Default constructor is fine for my purposes.
 */
class data{
public:

    /** Takes one argument and processes (split, trim, convert, verify) it before
     * sending it on for storage in the database. Returns success of the tests.
     * @param line a CSV-like string, separated by semicolons.
     * @see add()
     * @return The validity of the line parameter.
     */
    bool process(std::string line);

    /** Takes four arguments and stores them in the database. Returns success.
     * Automatically creates missing markets and stores, if encountered anew.
     * @param market A string holding the name of the marketplace.
     * @param store A string holding the name of the store.
     * @param product A string holding the name of the product.
     * @param cost A double holding the price of the product.
     * @see process()
     * @return Success.
     */
    bool add(std::string market, std::string store, std::string product, double cost);

    /** Prints the names of each marketplace in the database.
     */
    void chains();

    /** Prints the names of each store in the marketplace.
     * @param market_name A string holding the name of the market you want to
     * find the stores for.
     */
    void stores(std::string market_name);

    /** Prints the name and price of each product in a store in a marketplace.
     * @param market A string holding the name of the market you want to find
     * the store in.
     * @param store A string holding the name of the store for which you want
     * to find the product information.
     */
    void products(std::string market, std::string store);


    /** Finds the cheapest stores (and the marketplaces in which they can be
     * found) for a given product. Scours the whole database, looking in each
     * marketplace and each store. Only one parameter is needed:
     * @param name A string holding the name of the product you are interested in.
     */
    void cheapest(std::string name);

private:
    /** This is where the magic happens. My data structure of choice would have been
     * map<string, map<string, map<string, double>>>, not
     * map<string, map<string, vector<string, double>>> but oh well. I'm not changing
     * it now.
     */
    //3ICE: Some compilers do not like >>> ending, so I added spaces between each:
    std::map<std::string, std::map<std::string, std::vector<product> > > database;
    //3ICE: Look at this "std::" spam :(
    //3ICE: No, "using namespace std" is forbidden in headers.
    std::map<std::string, std::map<std::string, std::vector<product> > >::iterator store_iterator;
    std::map<std::string, std::vector<product> >::iterator market_iterator;
    std::vector<product>::iterator product_iterator;
    //3ICE: No const iterators for now, thank you. Maybe in my next project.
};

#endif // DATA_HH
