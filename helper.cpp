#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "helper.h"
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
    while (true){
        string s; fin >> s;
        cout << s << "\n";
        if (fin.eof()){
            break;
        }
    }
    cout << endl;
}