#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_map<string, void(*)(void)> commands;

void help(){
    cout << "all commands: \n";
    for (auto i : commands){
        cout << i.first << "\n";
    }
    cout << endl;
}
void add(){
    cout << "add" << endl;
}
void view(){
    cout << "view" << endl;
}
void fillCommands(){
    void (*functptr[])() = {help, add, view};
    string commandsFile = "commands.txt";
    ifstream fin(commandsFile);
    int ctr = 0;
    while (true){
        string s; fin >> s;
        if (fin.eof()){
            break;
        }
        commands[s] = functptr[ctr++];
    }
}

int main(){
    fillCommands();
    while (true){
        cout << "Enter command:\n";
        string command; cin >> command;
        transform(command.begin(), command.end(), command.begin(), [](unsigned char c){return tolower(c);});
        cout << endl;
        if (!command.compare("exit")){
            cout << "Quit program\n\n";
            break;
        }
        if (!commands.count(command)){
            cout << "Please enter in a valid command. Type 'help' to view commands\n\n";
            continue;
        }
        commands[command]();
    }
    return 0;
}