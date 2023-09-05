#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include "helper.hpp"
using namespace std;

struct food{
    string name, calories, fats, carbs, protein;
};

typedef struct food food;

void quit();
void fillCommands();
void help();
void loadFoods();
void addFood(food f);
food getFoodInfo();
void add();
void view();

unordered_map<string, void(*)(void)> commands; //lolz sorry global variable
unordered_map<string, food> foods;

void quit(){
    return;
}

void fillCommands(){
    void (*functptr[])() = {&help, &add, &view, &quit};
    string cmds[4] = {"help", "add", "view", "quit"};
    for (int i = 0; i < 4; ++i){
        commands[cmds[i]] = functptr[i];
    }
}

void help(){
    cout << "All commands: \n";
    for (auto i : commands){
        cout << i.first << "\n";
    }
    cout << endl;
}

void loadFoods(){
    ifstream fin("foods.txt");
    string s;
    for (int i = 0; i < 5; ++i){
        fin >> s;
    }
    while (true){
        string name; fin >> name;
        if (fin.eof()){
            break;
        }
        string calories, fats, carbs, protein;
        fin >> calories >> fats >> carbs >> protein;
        food f = {name, calories, fats, carbs, protein};
        foods[name] = f;
    }
}

void addFood(food f){
    ofstream fout;
    fout.open("foods.txt", ios_base::app);
    fout << f.name << " " << f.calories << " " << f.fats << " " << f.carbs << " " << f.protein << endl;
}

//name, calories, fats, carbs, protein
food getFoodInfo(){
    string name = prompt("Enter food name\n");
    if (foods.count(name)){
        return foods[name];
    }
    string calories = prompt("Enter calories\n");
    string fats = prompt("Enter fats\n");
    string carbs = prompt("Enter carbs\n");
    string protein = prompt("Enter protein\n");
    food ret = {name, calories, fats, carbs, protein};
    foods[name] = ret;
    addFood(ret);
    return ret;
}

void add(){
    while (true){
        cout << "Enter date (mmddyyyy)" << endl;
        string date; cin >> date;
        toLower(date);
        if (!date.compare("exit") || !date.compare("quit")){
            break;
        }
        string file = "data/"+ date + ".txt";
        ofstream fout;
        if (fileExists(file)){
            cout << "append\n";
        }
        else{
            cout << "new file\n";
        }
        
        while (true){
            cout << "Enter new food? (Y/N)\n";
            string s; cin >> s;
            if (!s.compare("N") || !s.compare("n")){
                break;
            }
            food f = getFoodInfo();
            cout << f.name << " " << f.calories << " " << f.fats << " " << f.carbs << " " << f.protein << endl;
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
    loadFoods();
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