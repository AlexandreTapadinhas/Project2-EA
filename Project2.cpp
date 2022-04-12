/*
Rui Alexandre Tapadinhas - 2018283200
David Marcelino Mendes Palaio - 2018283864

Mooshak 
*/
/*
g++ -std=c++17 -Wall -Wextra -O2 Project2.cpp -lm
*/

/* Expected output for input.txt
2 10
3 91
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <istream>
#include <sstream>
#include <map>

#define MAX_LINE 100

using namespace std;

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited, map< int, vector<int, vector<int>> > &ratings);
void rec(int no_ind, map<int,vector<int>> &scheme, vector<bool> &visited, map <int, vector<int, vector<int>>> &ratings, vector<int> &leafs);

int main () {

    string line;
    stringstream line_ss(line);

    map< int, vector<int> > pyramid_scheme;
    vector<bool> visited;
    int recruiter, aux, num_nodes;
    /* score obtained by using or not using the node 
    rating[node] = [nodes visited when not used, total money when not used]
                or [nodes visited when used, total money when used] */
    map <int, vector<int, vector<int>>> ratings; 
    int num_nodes_visited = 0;

    

    while (getline(cin, line)) {
        istringstream line_ss(line);
        line_ss >> recruiter;
        vector<int> recruited;
        if (recruiter != -1) {
            while(line_ss >> aux) {
                recruited.push_back(aux);
            }

            pyramid_scheme[recruiter] = recruited;
        }
        else {
            num_nodes = pyramid_scheme.size();
            visited.resize(num_nodes);
            solve_pyramid_scheme(pyramid_scheme, visited, ratings);
            cout << endl;
            pyramid_scheme.clear();
            ratings.clear();
            num_nodes_visited = 0;
        }
    }
    return 0;
}

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited, map< int, vector<int, vector<int>> > &ratings) {
    vector <int> parents;

    vector<int> sons = vector<int>(scheme[0].begin(), scheme[0].end()-1);
    for (int son :sons) {
        rec(son, scheme, visited, ratings, parents);
    }

    vector<int> parents_in_order_of_visiting = vector<int>(parents.rbegin(), parents.rend());

    for (int p: parents_in_order_of_visiting) {
        cout << p << " ";
    }

}

void rec(int no_ind, map<int,vector<int>> &scheme, vector<bool> &visited, map <int, vector<int, vector<int>>> &ratings, vector<int> &parents) {
    vector<int> sons = vector<int>(scheme[no_ind].begin(), scheme[no_ind].end()-1); // slice list to only have the children and not the cost of the node
    if (sons.size() == 0) {
        cout << "leaf" << endl;
        // scheme[no_ind][0] is where the cost of the node is stored
        vector<int, vector<int>> aux;
        //vector<int> aux_line;
        aux[0][0] = vector<int>(aux.begin(), aux.end());
        aux[1] = {1, scheme[no_ind][0]};

        ratings[no_ind] = ;
    }
    else {
        parents.push_back(no_ind);
        for (int son :sons) {
            rec(son, scheme, visited, ratings, parents);
        }
    }
}