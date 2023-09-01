#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

struct food{
    string name, calories, fats, carbs, protein;
};

typedef struct food food;

void quit();
void fillCommands();
bool fileExists(string file);
void toLower(string& s);
void help();
string prompt(string ques);
void loadFoods();
void addFood(food f);
food getFoodInfo();
void add();
void readFile(string file);
void view();

unordered_map<string, void(*)(void)> commands; //lolz sorry global variable
unordered_map<string, food> foods;

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

string prompt(string ques){
    cout << ques;
    string ret; cin >> ret;
    return ret;
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
    fout << endl << f.name << " " << f.calories << " " << f.fats << " " << f.carbs << " " << f.protein << endl;
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