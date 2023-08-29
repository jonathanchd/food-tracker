#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

void quit();
void fillCommands();
bool fileExists(string file);
void toLower(string& s);
void help();
void add();
void readFile(string file);
void view();

unordered_map<string, void(*)(void)> commands; //lolz sorry global variable

void quit(){
    return;
}

void fillCommands(){
    void (*functptr[])() = {&help, &add, &view};
    string commandsFile = "commands.txt";
    ifstream fin(commandsFile);
    int ctr = 0;
    while (true){
        string s; fin >> s;
        commands[s] = functptr[ctr++];
        if (fin.eof()){
            break;
        }
    }
}

bool fileExists(string file){
    return filesystem::exists(file);
}

void toLower(string& s){
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return tolower(c);});
}

void help(){
    cout << "All commands: \n";
    for (auto i : commands){
        cout << i.first << "\n";
    }
    cout << endl;
}

void add(){
    cout << "add\n\n";
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

void view(){
    while (true){
        cout << "Enter date (mmddyyyy)" << endl;
        string date; cin >> date;
        toLower(date);
        if (!date.compare("exit") || !date.compare("quit")){
            break;
        }
        string file = "data/"+ date + ".txt";
        if (fileExists(file)){
            cout << "valid\n\n";
            readFile(file);
        }
        else{
            cout << "file does not exist\n\n";
        }
    }
}

int main(){
    fillCommands();
    while (true){
        cout << "Enter command:\n";
        string command; cin >> command;
        toLower(command);
        cout << endl;
        if (!command.compare("exit") || !command.compare("quit")){
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