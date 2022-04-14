/*
Rui Alexandre Tapadinhas - 2018283200
David Marcelino Mendes Palaio - 2018283864

Mooshak 
*/
/*
g++ -std=c++17 -Wall -Wextra -O2 Project2_1.cpp -lm
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

void solve_pyramid_scheme(int father_node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings);

int main () {

    string line;
    stringstream line_ss(line);

    map< int, vector<int> > pyramid_scheme;
    vector<bool> visited;
    int recruiter, aux;
    /* score obtained by using or not using the node 
    rating[node] = {{nodes visited when not used, total money when not used},
                    {nodes visited when used, total money when used}} */
    map <int, vector<vector<int>>> ratings; 

    

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
            solve_pyramid_scheme(0, pyramid_scheme, ratings);
            cout << ratings[0][1][0] << " " << ratings[0][1][1] << endl;
            pyramid_scheme.clear();
            ratings.clear();
        }
    }
    return 0;
}

void solve_pyramid_scheme(int father_node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings) {
    vector<int> sons = vector<int>(scheme[father_node].begin(), scheme[father_node].end()-1); // slice list to only have the children and not the cost of the node

    ratings[father_node] = {{1, scheme[father_node][(int)scheme[father_node].size()-1]}, {0, 0}};

    for (int son: sons) {
        solve_pyramid_scheme(son, scheme, ratings);
        if (ratings[son][0][0] > ratings[son][1][0]) {
            ratings[father_node][0][0] += ratings[son][1][0];
            ratings[father_node][0][1] += ratings[son][1][1];
        }
        else if (ratings[son][0][1] < ratings[son][1][1]) {
            ratings[father_node][0][0] += ratings[son][0][0];
            ratings[father_node][0][1] += ratings[son][1][1];
        }
        else if (ratings[son][0][0] < ratings[son][1][0]) {
            ratings[father_node][0][0] += ratings[son][0][0];
            ratings[father_node][0][1] += ratings[son][0][1];
        }
        else { // if (ratings[son][0][1] > ratings[son][1][1])
            ratings[father_node][0][0] += ratings[son][0][0];
            ratings[father_node][0][1] += ratings[son][0][1];
        }
        ratings[father_node][1][0] += ratings[son][0][0];
        ratings[father_node][1][1] += ratings[son][0][1];
    }
}

