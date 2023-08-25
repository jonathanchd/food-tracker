#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;


void fillCommands(unordered_set<string>& commands){
    string commandsFile = "commands.txt";
    ifstream fin(commandsFile);
    while (true){
        string s; fin >> s;
        if (fin.eof()){
            break;
        }
        commands.insert(s);
    }
}



int main(){
    unordered_set<string> commands;
    fillCommands(commands);
    while (true){
        cout << "Enter command:\n";
        string command; cin >> command;
        if (commands.find(command) == commands.end()){
            cout << "Please enter in a valid command. Type 'help' to view commands\n";
            continue;
        }
    }
    return 0;
}