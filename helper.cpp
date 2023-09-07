#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "helper.hpp"
using namespace std;

bool fileExists(string file){
    return filesystem::exists(file);
}

void toLower(string& s){
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return tolower(c);});
}

string prompt(string ques){
    cout << ques;
    string ret; cin >> ret;
    return ret;
}

void readFile(string file){
    ifstream fin(file);
    string dates[3];
    dates[0] = file.substr(5, 2) + "/";
    dates[1] = file.substr(7, 2) + "/";
    dates[2] = file.substr(9, 4);
    cout << "Reading from ";
    for (int i = 0; i < 3; ++i){
        cout << dates[i];
    }
    cout << "\n";
    int counter = 0;
    while (!fin.eof()){
        string s; fin >> s;
        cout << s + " ";
        ++counter;
        if (counter == 7){
            counter = 0;
            cout << endl;
        }
    }
    cout << endl;
}