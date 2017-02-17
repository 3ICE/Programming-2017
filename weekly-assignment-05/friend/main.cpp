#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
using Friends = set<string>;
using FriendGroup = map<string, Friends>;
// typedef set<string> Friends;
// typedef map<string, Friends> FriendGroup;

//So FriendGroup is map<string, set<string>>

void print_friends(const FriendGroup& network);
void print_friends2(const FriendGroup& network);
bool add_friendship(FriendGroup& network, string a, string b);
void add_new_person(FriendGroup& network);
Friends common_friends(FriendGroup& network, string a, string b);

int main() {
    //map<string, set<string>> friendhips;
    FriendGroup friendhips = {
        { "Elisa", {"Anna", "Alex"} },
        { "Anna", {"Elisa",} },
        { "Alex", {"Elisa",} },
    };
    //print_friends(friendhips);cout<<endl;
    print_friends(friendhips);

    if(add_friendship(friendhips,"Anna", "Alex")) print_friends(friendhips);
    else cout<<"Name not found!"<<endl;

    add_new_person(friendhips);
    add_friendship(friendhips, "Elisa", "Minna");
    print_friends(friendhips);


    cout<<"Common friends of Elisa and Anna:"<<endl;
    Friends common = common_friends(friendhips, "Elisa","Anna");
    for (auto buddy:common) {
        cout<<buddy<<endl;
    }
}

//3ICE: Variation on teacher's much nicer code
void print_friends2(const FriendGroup& network){
    for(auto person: network){
        cout<<person.first<<endl;
        for(auto buddy:person.second) cout<<" "<<buddy<<endl;
    }
}

//3ICE: My code
void print_friends(const FriendGroup& network){
    FriendGroup::const_iterator iter = network.begin();
    while ( iter != network.end() ) {
        cout << iter->first << " is friends with:"<<endl;
        Friends::iterator it = iter->second.begin();
        while ( it != iter->second.end() ) {
            cout<<*it<<endl;
            ++it;
        }
        cout<<endl;
        ++iter;
    }
}

bool add_friendship(FriendGroup& n, string a, string b){
    if(n.find(a)!=n.end() && n.find(b)!=n.end()){
        n.at(a).insert(b);
        n.at(b).insert(a);
        return true;
    }
    return false;
}

void add_new_person(FriendGroup& n){
    cout<<"Enter name: ";
    string name;
    cin>>name;
    cout<<endl;
    n.insert({name, {} });
}

Friends common_friends(FriendGroup& n, string a, string b){
    if(n.find(a)==n.end() || n.find(b)==n.end()) return {};
    Friends common={};
    for(auto buddy: n.at(a)){
        //3ICE: I think this might be incorrect. Isn't n.at(b).end() the same as n.end()?
        //3ICE: Never mind, n.at(b) is a set not a map. Just a little extra work finding at(b) twice.
        if(n.at(b).find(buddy)!=n.at(b).end()) common.insert(buddy);
    }
    return common;
}
