/*
Rui Alexandre Tapadinhas - 2018283200
David Marcelino Mendes Palaio - 2018283864

Mooshak 
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

void solve_pyramid_scheme(int father_node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings);
void rec(int no_ind, map<int,vector<int>> &scheme, vector<bool> &visited, map <int, vector<vector<int>>> &ratings, vector<int> &leafs);
void rate_father_vs_all_children(int father_node, map<int,vector<int>> &scheme, map <int, vector<vector<int>>> &ratings);

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
            solve_pyramid_scheme(0, pyramid_scheme, ratings);
            cout << ratings[0][1][0] << " " << ratings[0][1][1] << endl;
            pyramid_scheme.clear();
            ratings.clear();
            //cout << "done" << endl;
        }
    }
    return 0;
}

void solve_pyramid_scheme(int father_node, map < int, vector<int> > &scheme, map< int, vector<vector<int>> > &ratings) {
    vector<int> melhor_soma_filhos{1, scheme[father_node][(int)scheme[father_node].size()-1]};
    vector<int> sons = vector<int>(scheme[father_node].begin(), scheme[father_node].end()-1); // slice list to only have the children and not the cost of the node

    //vector<int> sum_price_sons{0, 0};
    // rating using 
    //vector<vector<int>> temp_rating_son{{0, 0}, {0, 0}};
    ratings[father_node] = {{1, scheme[father_node][(int)scheme[father_node].size()-1]}, {0, 0}};

    for (int son: sons) {
        solve_pyramid_scheme(son, scheme, ratings);
        //temp_rating_son = ratings[son];
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
    //ratings[father_node] = {melhor_soma_filhos, sum_price_sons};
}

