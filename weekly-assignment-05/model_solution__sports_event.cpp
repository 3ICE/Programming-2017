#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


void add_ranking(map<string, vector<string>>& rankings,
                 const string& event_name,
                 const string& competitor) {

    map<string, vector<string>>::iterator event_iter;
    event_iter = rankings.find(event_name);

    if ( event_iter == rankings.end() ) {
        rankings.insert( { event_name, { competitor } } );

    } else {

        event_iter->second.push_back(competitor);
    }
}


void print_rankings(const map<string, vector<string>>& rankings) {
    map<string, vector<string>>::const_iterator event_iter;
    event_iter = rankings.begin();

    while ( event_iter != rankings.end() ) {
        cout << event_iter->first << endl;

        vector<string>::const_iterator competitor_iter;
        competitor_iter = event_iter->second.begin();

        int sijoitus = 1;
        while ( competitor_iter != event_iter->second.end() ) {
            cout << "  " << sijoitus << ". " << *competitor_iter << endl;

            ++sijoitus;
            ++competitor_iter;
        }

        ++event_iter;
    }
}


int main() {
    map<string, vector<string>> ranking_map;

    while ( true ) {
        cout << "Event: ";
        string event;
        getline(cin, event);

        if ( event.empty() ) {
            break;
        }

        cout << "Competitor: ";
        string competitor;
        getline(cin, competitor);

        if ( competitor.empty() ) {
            break;
        }

        add_ranking(ranking_map, event, competitor);
    }

    print_rankings(ranking_map);
}
