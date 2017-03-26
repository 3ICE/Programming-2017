/** @see "data.hh" for detailed documentation of each function.
 * (I wish I knew which file to put function documentation in.
 * Hate repeating myself. Maybe I should have defined all my
 * functions in the header to avoid this confusion.)
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#include "data.hh"
using namespace std;

/**
 * @brief data::process checks the input for possible errors
 * @param line, a CSV string
 * @return success
 * @see "data.hh" for full documentation
 */
bool data::process(string line){
    //cout<<line<<endl;
    Splitter s(line);
    s.split(';');
    //3ICE: error checking step: "must contain 3 semicolons" (testcases: bad_2, bad_3, bad_4, and bad_5)
    if(s.number_of_fields()!=4) return false;

    double price;
    //3ICE: error checking step: "last field must be double" (testcase: bad_1)
    try{
        //3ICE: Convert from string:
        price = stod(s.fetch_field(3));
    }
    catch(exception) {
        return false;
    }

    //3ICE: error checking step: "can't contain spaces" (testcases: bad_6, and bad_8)
    if(line.find_first_of(" \t") != string::npos) return false;

    //3ICE: error checking step: "none of the fields are allowed to be empty" (testcase: bad_7)
    if(  s.fetch_field(0).length()==0 ||
         s.fetch_field(1).length()==0 ||
         s.fetch_field(2).length()==0 ||
         s.fetch_field(3).length()==0) return false;

    return add(s.fetch_field(0), s.fetch_field(1), s.fetch_field(2), price);
}

/**
 * @brief data::add stores parameters in database
 * @param market string name of marketplace
 * @param store string name of store
 * @param name string product name
 * @param cost double price of product
 * @return success
 * @see "data.hh" for real documentation
 */
bool data::add(string market, string store, string name, double cost){
    if(database.find(market) != database.end()){
        //3ICE: Marketplace already exists.
        if(database.at(market).find(store) != database.at(market).end()){
            //3ICE: Store already exists.
            //if(database.at(market).at(store).find(name) != database.at(market).at(store).end())
            bool overwrite = false;
            for (int i = 0; i < database[market][store].size(); ++i) {
                if(database[market][store][i].name == name){
                    //3ICE: Product already exists. Gotta change its price:
                    overwrite = true;
                    database[market][store][i].price = cost;
                } //3ICE: his check was required because:
                //3ICE: If the same product is given to the same store more than once,
                //3ICE: the last one of them will be used as an actual value (price).
            }
            //3ICE: Interestingly, this did not work:
            //for(auto p : database[market][store]) if(p.name == name) p.price = cost;
            //3ICE: Copy constructor called?

            //3ICE: We did not find an already existing product with this name. Create it:
            if(!overwrite) database.at(market).at(store).push_back(product(name, cost));
        }else{
            //3ICE: Store does not exist yet, create and fill it with one product:
            database.at(market).insert({store, {product(name, cost)}} );
        }
    }else{
        //3ICE: Marketplace doesn't exist. Create it,
        database[market]=map<string, vector<product>>();
        //3ICE: and fill the store inside it with first data point:
        database[market][store] = {product(name, cost)};
    }
    return true;
}


/**
 * @brief data::chains prints markets
 * @see also "data.hh"
 */
void data::chains(){
    vector<string> chain_names;
    //3ICE: C++11 auto for loops are beautiful
    for(auto marketplace : database){
        chain_names.push_back(marketplace.first);
    }
    sort(chain_names.begin(), chain_names.end());
    cout << chain_names.size() << endl;
    for(auto chain_name : chain_names){
        cout << chain_name << endl;
    }
}

/**
 * @brief data::stores prints stores in a market
 * @param market_name which market you want
 * @see "data.hh"
 */
void data::stores(string market_name){
    vector<string> stores;
    if(database.find(market_name) == database.end()){
        cout << "Error: Market " << market_name << " not found in database." << endl;
        return;
    }
    for(market_iterator=database.at(market_name).begin();market_iterator!=database.at(market_name).end();++market_iterator){
        stores.push_back(market_iterator->first);
    }
    sort(stores.begin(), stores.end());
    for(auto store : stores){
        cout << store << endl;
    }
}

/**
 * @brief data::products lists all products for sale in then given market's store
 * @param market string name of
 * @param store string name of
 * @see "data.hh"
 */
void data::products(string market, string store){
    vector<product> products;
    //3ICE: Make sure they exist before using .at() recklessly:
    if(database.find(market) == database.end()){
        cout << "Error: Market " << market << " not found in database." << endl;
        return;
    }
    if(database.at(market).find(store) == database.at(market).end()){
        cout << "Error: Store " << store << " not found in database." << endl;
        return;
    }
    //3ICE: Now it is safe to use db.at(m).at(s) as we are sure they both exist:
    for(product_iterator = database.at(market).at(store).begin();
        product_iterator != database.at(market).at(store).end();
        ++product_iterator){
        products.push_back(*product_iterator);
    }
    sort(products.begin(), products.end());
    for(auto product : products){
        //3ICE: Instead of doing any of these ugly things:
        //(*product_iterator).print(); /* or */
        //cout << product_iterator->name << endl << product_iterator->price << endl;
        //3ICE: I can simply:
        product.print();
    }
}

/**
 * @brief data::cheapest finds the best deals.
 * @param name which product to look for
 * @see "data.hh" as always
 */
void data::cheapest(string name){
    double cheapest_price = numeric_limits<double>::max();//3ICE: I was hoping to do a min search instead, but:
    //min_element(database.begin(), database.end(),
    //            [](double l, double r) -> bool { return l.second < r.second; });
    vector<string> results;
    for(store_iterator = database.begin();
        store_iterator != database.end();
        ++store_iterator){
        for(market_iterator = store_iterator->second.begin();
            market_iterator != store_iterator->second.end();
            ++market_iterator){
            for(product_iterator = market_iterator->second.begin();
                product_iterator != market_iterator->second.end();
                ++product_iterator){
                //cout<<product_iterator->name<<endl;
                if(product_iterator->price <= cheapest_price && product_iterator->name == name){
                    //3ICE: Only reset if we found a cheaper minimum.
                    if(product_iterator->price < cheapest_price){
                        cheapest_price = product_iterator->price;
                        results.clear();
                    }
                    //3ICE: Record the marketplace and store information for later printing.
                    results.push_back(store_iterator->first + " " +market_iterator->first );
                }
            }
        }
    }

    if(cheapest_price == numeric_limits<double>::max()) cout << "This product is not available anywhere." << endl;
    else{
        //3ICE: The price will be printed with two decimals.
        cout << setprecision(2) << fixed << cheapest_price << endl;
        //Store chain names are in alphabetical order and if there are multiple stores that have
        //the same cheapest price for the product they will in turn be in alphabetical sub-order.
        sort(results.begin(), results.end());
        for(auto result : results){
            cout << result << endl;
        }
    }
}
