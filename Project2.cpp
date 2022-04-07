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

void find_pyramid_scheme(map < int, vector<int> > &scheme);

int main () {

    string line;
    stringstream line_ss(line);
    //getline(cin, line);

    map< int, vector<int> > pyramid_scheme;
    int recruiter, aux;

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
            find_pyramid_scheme(pyramid_scheme);
            cout << endl;
            pyramid_scheme.clear();
        }

    }
    return 0;
}

void find_pyramid_scheme(map < int, vector<int> > &scheme) {
    for (auto &pair: scheme) {
        cout << "{" << pair.first << ": ";
        for (auto &recruited: pair.second) {
            cout << recruited << " ";
        }
        cout << "}" << endl;
    }
}