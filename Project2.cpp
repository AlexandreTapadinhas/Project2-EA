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

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited, map< int, vector<vector<int>> > &ratings);
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
            solve_pyramid_scheme(pyramid_scheme, visited, ratings);
            cout << endl;
            pyramid_scheme.clear();
            ratings.clear();
        }
    }
    return 0;
}

void solve_pyramid_scheme(map < int, vector<int> > &scheme, vector<bool> &visited, map< int, vector<vector<int>> > &ratings) {
    vector <int> parents;

    rec(0, scheme, visited, ratings, parents);

    vector<int> parents_in_order_of_visiting = vector<int>(parents.rbegin(), parents.rend());

    for (int p: parents_in_order_of_visiting) {
        cout << "parent = " << p << endl;
        rate_father_vs_all_children(p, scheme, ratings);
    }

    cout << "ratings root = " << ratings[0][0][0] << " " << ratings[0][0][1] << endl << "\t\t" << ratings[0][1][0] << " " << ratings[0][1][1];

}

void rec(int no_ind, map<int,vector<int>> &scheme, vector<bool> &visited, map <int, vector<vector<int>>> &ratings, vector<int> &parents) {
    //cout << "no_ind = " << no_ind << endl;
    vector<int> sons = vector<int>(scheme[no_ind].begin(), scheme[no_ind].end()-1); // slice list to only have the children and not the cost of the node
    if (sons.size() == 0) {
        cout << "leaf" << endl;
        // scheme[no_ind][0] is where the cost of the node is stored
        vector<vector<int>> aux;
        aux.resize(2, vector<int>(2));
        //vector<int> aux_line;
        aux[0].push_back(0);aux[0].push_back(0);
        aux[1].push_back(1);aux[1].push_back(scheme[no_ind][0]);
        // {{0,0},{1, scheme[no_ind][0]}}
        ratings[no_ind] = aux;
    }
    else {
        parents.push_back(no_ind);
        for (int son :sons) {
            rec(son, scheme, visited, ratings, parents);
        }
    }
}

void rate_father_vs_all_children(int father_node, map<int,vector<int>> &scheme, map <int, vector<vector<int>>> &ratings) {
    vector<int> sons = vector<int>(scheme[father_node].begin(), scheme[father_node].end()-1); // slice list to only have the children and not the cost of the node
    int father_price = vector<int>(scheme[father_node].end()-1, scheme[father_node].end())[0]; // price of the father node is on the end of the array of the children
    
    /*cout << "num of sons = " << (int)sons.size() << endl; 
    vector<vector<int>> aux;
    aux.resize(2, vector<int>(2));
    //vector<int> aux_line;
    aux[0][0] = 1 + (int)sons.size();
    aux[0][1] = father_price;
    aux[1][0] = (int)sons.size();
    //sum of the price of all the children
    int sum = 0;
    for (int son: sons) {
        sum += ratings[son][1][1];
    }
    cout << "sum of price of all children = " << sum << endl;
    aux[1][1] = sum;
    
    cout << "aux[1][0] = " << aux[1][0] << "\taux[0][0] = " << aux[0][0] << endl;
    if (aux[1][0] > aux[0][0]) {
        cout << "entrei\n\n\n" << endl;
        aux[0][0] = aux[1][0];
        aux[0][1] = aux[1][1];
    }
    ratings[father_node] = aux;*/
    int num_sons = (int)sons.size();
    int sum = 0;
    for (int son: sons) {
        sum += vector<int>(scheme[son].end()-1, scheme[son].end())[0]; // price of the father node is on the end of the array of the children
    }
    if () { // TODO: verificar se a melhor opçao é escolher todos os filhos ou só o pai

    }

}