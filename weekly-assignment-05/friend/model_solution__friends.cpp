#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;


using FriendSet     = set<string>;
using FriendshipMap = map<string, FriendSet>;


bool does_person_exist(const FriendshipMap& net, const string& name);
bool are_they_friends(const FriendshipMap& net,
                      const string& name1, const string& name2);
void add_friendship(FriendshipMap& net,
                    const string& name1, const string& name2);
void print(const FriendshipMap& net);
FriendSet common_friends(const FriendshipMap& net,
                         const string& name1, const string& name2);


int main() {
    FriendshipMap friendships = {
        { "Matti", { "Tero", "Eero"} },
        { "Eero",  { "Matti" } },
        { "Tero",  { "Matti" } },
    };

    // From now on bool values will print out as true and false
    // instead of the usual 1 and 0.
    cout << boolalpha;

    // Testing does_person_exist function.
    cout << does_person_exist(friendships, "Risto") << endl;
    cout << does_person_exist(friendships, "Matti") << endl;

    // Testing are_they_friends function.
    cout << are_they_friends(friendships, "Tero", "Eero") << endl;
    cout << are_they_friends(friendships, "Tero", "Matti") << endl;

    // Let's add some realationships present in the
    // problem.  Just to add more data for testing.
    add_friendship(friendships, "Elina", "Erkki");
    add_friendship(friendships, "Elina", "Eero");
    add_friendship(friendships, "Erkki", "Matti");
    add_friendship(friendships, "Matti", "Jaakko");
    add_friendship(friendships, "Eero",  "Erkki");

    print(friendships);

    for ( auto common : common_friends(friendships, "Elina", "Matti") ) {
        cout << common << endl;
    }
}


// Returns true in «name» exists in the «net».
// Returns false otherwise.
bool does_person_exist(const FriendshipMap& net, const string& name) {
    return net.find(name) != net.end();

    // if ( net.find(name) != net.end() ) {
    //     return true;
    // } else {
    //     return false;
    // }
}


// Returns true if «name1» ja «name2» are friends
// based on the information in the «net».
// Otherwise returns false.
bool are_they_friends(const FriendshipMap& net,
                      const string& name1,
                      const string& name2) {
    if ( not does_person_exist(net, name1)
           or not does_person_exist(net, name2) ) {
        return false;
    }

    return net.at(name1).find(name2) != net.at(name1).end();

    // if ( net.at(name1).find(name2) != net.at(name1).end() ) {
    //     return true;
    // } else {
    //     return false;
    // }
}


// Add the information to the «net» stating that «name1» ja «name2»
// are friends.  If the relationship already existed, no need to
// do anything.
void add_friendship(FriendshipMap& net,
                    const string& name1, const string& name2) {

    // They were already friends, no need to do anything.
    if ( are_they_friends(net, name1, name2) ) {
        return;
    }

    // Let's make sure both persons exist.
    for ( string name : { name1, name2 } ) {
        if ( not does_person_exist(net, name) ) {
            // Add person of he/she did not exist before.
            net.insert( { name, {} } );
        }
    }

    // Here we add the relationship in both ways.
    // it is safe to use at-method to access the map,
    // since we just made sure above that both names
    // exist in the «net».
    net.at(name1).insert(name2);
    net.at(name2).insert(name1);
}


// The whole network of friendships is dumped on the screen.
void print(const FriendshipMap& net) {
    for ( auto person : net ) {
        cout << person.first << endl;

        for ( auto kaveri : person.second ) {
            cout << "  " << kaveri << endl;
        }
    }
}


// Returns the commond friends of two persons.
// The there are no common friends or one or both
// of the names don't exist, returns an empty set.
FriendSet common_friends(const FriendshipMap& net,
                         const string& name1,
                         const string& name2) {

    // One of both are unknown.
    if ( not does_person_exist(net, name1)
            or not does_person_exist(net, name2) ) {
        return {};
    }

    FriendSet common_friends = {};

    // All the names that are both in the «name1»'s friend set
    // and «name2»'s friend set are added to the set of
    // common friends.
    for ( auto friend_name : net.at(name1) ) {
        if ( are_they_friends(net, friend_name, name2) ) {
            common_friends.insert(friend_name);
        }
    }

    return common_friends;
}
