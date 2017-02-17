#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
//Add information about an athlete (event, position, and name).
bool add(map<string, vector<string>>& a, string sport, int pos, string name);

//To print on the screen all the information contained in the data structure.
void print(const map<string, vector<string>>& a);

int main() {
    map<string, vector<string>> a{{ "ESPORTS", {} }};
    add(a,"ESPORTS",1,"Daniel");
    add(a,"Running",1,"Dad");
    add(a,"Javelin",1,"James Masters");
    add(a,"Javelin",6,"John Williams");
    add(a,"Pole Jump",1,"Jamie Jumper");
    add(a,"Pole Jump",9,"Sophie Poppenkorkken");
    add(a,"Marathon",1,"Marcus Aurelius");
    add(a,"Marathon",5,"Simon Steel");
    print(a);
}

void print(const map<string, vector<string>>& a){
    for(auto s: a){
        cout<<s.first<<endl;
        int i=1;
        for(auto p:s.second) cout<<i++<<" "<<p<<endl;
        cout<<endl;
    }
}


bool add(map<string, vector<string>>& a, string sport, int pos, string name){
    if(a.find(sport)==a.end()){
        a[sport]={};
    }
    if(a.at(sport).size()<pos) a.at(sport).resize(pos);
    a.at(sport)[pos-1]=name;
    return true;
}
