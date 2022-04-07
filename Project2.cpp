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

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited);
void rec(map<int,vector<int>> &scheme, vector<bool> &visited, int no_ind);

int main () {

    string line;
    stringstream line_ss(line);
    //getline(cin, line);

    map< int, vector<int> > pyramid_scheme;
    vector<bool> visited;
    int recruiter, aux, num_nodes;

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
            solve_pyramid_scheme(pyramid_scheme, visited);
            cout << endl;
            pyramid_scheme.clear();
        }
        pyramid_scheme.clear();
    }
    return 0;
}

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited) {
    /*for (auto &pair: scheme) {
        cout << "{" << pair.first << ": ";
        for (auto &recruited: pair.second) {
            cout << recruited << " ";
        }
        cout << "}" << endl;
    }*/

    vector<int> sons = vector<int>(scheme[0].begin(), scheme[0].end()-1);
    for (int son :sons) {
        rec(scheme, visited, son);
    }
}

void rec(map<int,vector<int>> &scheme, vector<bool> &visited, int no_ind) {
    vector<int> sons = vector<int>(scheme[no_ind].begin(), scheme[no_ind].end()-1);
    if (sons.size() == 0) {
        cout << "leaf" << endl;
    }
    for (int son :sons) {
        rec(scheme, visited, son);
    }
}