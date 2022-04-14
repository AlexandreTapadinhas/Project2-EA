/*
Rui Alexandre Tapadinhas - 2018283200
David Marcelino Mendes Palaio - 2018283864

Mooshak 
sub 622 - 200 ptos
*/
/*
g++ -std=c++17 -Wall -Wextra -O2 Project2_1.cpp -lm
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

void solve_pyramid_scheme(int node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings);

int main () {

    string line;
    stringstream line_ss(line);

    map< int, vector<int> > pyramid_scheme;
    vector<bool> visited;
    int recruiter, aux, num_nodes;
    /* score obtained by using or not using the node 
    rating[node] = [nodes visited when not used, total money when not used]
                or [nodes visited when used, total money when used] */
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
            num_nodes = pyramid_scheme.size();
            visited.resize(num_nodes);
            pyramid_scheme[-1] = {0, 0};
            solve_pyramid_scheme(-1, pyramid_scheme, ratings);
            cout << ratings[-1][0][0]-1 << " " << ratings[-1][0][1] << endl;
            pyramid_scheme.clear();
            ratings.clear();
        }
    }
    return 0;
}


void solve_pyramid_scheme(int node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings) {
    vector<int> sons = scheme[node];
    vector<int> rating_using_node{1, sons.back()};
    vector<int> rating_using_sons{0, 0};
    vector<vector<int>> temp{{0, 0}, {0, 0}};
    sons.pop_back();
    for (int son: sons) {
        solve_pyramid_scheme(son, scheme, ratings);
        temp = ratings[son];
        if (temp[0][0] > temp[1][0])
        {
            rating_using_node[0] += temp[1][0];
            rating_using_node[1] += temp[1][1];
        }
        else if (temp[0][0] < temp[1][0])
        {
            rating_using_node[0] += temp[0][0];
            rating_using_node[1] += temp[0][1];
        }
        else if (temp[0][1] < temp[1][1])
        {
            rating_using_node[0] += temp[0][0];
            rating_using_node[1] += temp[1][1];
        }
        else
        {
            rating_using_node[0] += temp[0][0];
            rating_using_node[1] += temp[0][1];
        }
        rating_using_sons[0] += temp[0][0];
        rating_using_sons[1] += temp[0][1];
    }
    ratings[node] = {rating_using_node, rating_using_sons};
}