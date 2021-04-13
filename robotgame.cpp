// T04_G02
#include <iostream>
#include <chrono>  // can handle with time
#include <thread>
#include <fstream>  // used for file handling
#include <vector>
#include "gamestructs.hpp"  // contains structs created for the game
using namespace std;

// declaring functions
void menu();
void rules(bool &programExecuting);
void play(bool &programExecuting);
bool fileExists(string fileName);
void getMapSize(ifstream &mapFile, int &height, int &width);
void getMapVector(ifstream &mapFile, vector <vector <char>> &map);
void printMap(vector <vector <char>> map);
void getGameInfo(vector <vector <char>> map, Player &P);


int main() {

    bool programExecuting = true;
    const int TIMESLEEP = 2;  // sleep functions are being used for test purposes
    
    while(programExecuting){  // infinite loop to keep the program running until the user wants to stop
        int menuOption;
        menu();
        cin >> menuOption;
        if (cin.eof()){  // closes program with CTRL-Z (Windows) or CTRL-D (Linux)
            break;
        }
        if (cin.fail()){  // checks for input type errors and sets menuOption to a "safe" invalid value
            const int safeNumber = 3;
            cin.clear();
            cin.ignore(1);
            menuOption = safeNumber;
        }

        switch(menuOption){  // selects menu option
            case 0:                                                     // Exit (program shuts down)
                programExecuting = false;
                cout << "Thanks for playing";
                break;
            case 1:                                                     // Rules (displays the rules of the game)
                rules(programExecuting);
                break;
            case 2:                                                     // Play (starts game)
                play(programExecuting);
                break;
            default:                                                    // in case no valid option is selected
                cout << "\nPlease choose a valid option" << endl;
                this_thread::sleep_for(chrono::seconds(TIMESLEEP));


        }
        
    }
    
    


    return 0;
}

void menu(){  // function to draw menu
    cout << "-----------------------------------------------------\n"
         << "                     ROBOTS GAME                     \n"
         << "                                                     \n"
         << "                      1) Rules                       \n"
         << "                      2) Play                        \n"
         << "                      0) Exit                        \n"
         << "                                                     \n"
         << "               Select your option: ";         
}

void editInput(string &input){
    int pos = input.find(' ');
    input = input.substr(0, pos);
}

void rules(bool &programExecuting){  // function to display rules
    char exitRules;
    cout << "\nRULES\n\nYou can exit the game at any time with CTRL-Z (Windows) or CTRL-D (Linux)"
         << "\nSymbols:"
         << "\n- * = electrical fence or post;"
         << "\n- H = player (alive); h = player (dead); the player dies when he/she collides with a fence or a post, or is captured by a robot;"
         << "\n- R = robot (alive); r = robot (destroyed=dead/stuck); a dead robot is one that collided with a fence or a post; a stuck robot is one that collided with another robot (alive or destroyed)"
         << "\nMovement:"
         << "\n- The player can only move to one of the 8 neighbour cells of his/her current cell."
         << "\n    Q              W              E"
         << "\n    A            player           D"
         << "\n    Z              X              C"
         << "\n- The player has the option to stay in his/her current position by typing 'S'."
         << "\n- The player can't move to cells occupied by destroyed robots"
         << "\n- Each robot can move to one of the 8 neighbour cells of its current cell, as the player."
         << "\nOther important info:"
         << "\n- When several robots collide, they get stuck and they are all represented by a single symbol, an 'r'."
         << "\n- When a robot collides with other destroyed robots ('r' cells) it also gets stuck."
         << "\n- If a robot collides with fences/posts it dies, being also represented by an 'r', and the fence/post cell at the position of the collision loses its capability to electrocute."
         << "\nPress any character when you're ready to leave";
    cin >> exitRules;  // wait for user input to return to menu
    if (cin.eof())     // more CTRL-Z CTRL-D stuff
        programExecuting = false;

}

void play(bool &programExecuting){  // function to play the game
    string mapNumber, mapFilePath, firstLine, currentLine;
    bool noFile = true;  // loop variable for file check
    bool run = true;  // variable to keep game going
    int mapHeight, mapWidth;  // map dimensions
    vector <vector <char>> map;  // map stored in a vector
    struct Player P;

    // run loop until a existing file is found
    while(noFile){ 
        cin.ignore(1);  // cleans input allowing getline() to wait for input
        cout << "\nSelect which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << endl;    
        getline(cin, mapNumber);
        if (mapNumber == "0"){
            return;
        }
        if (cin.eof()){
            programExecuting = false;
            return;
        }
        mapFilePath = "MAZE_" + mapNumber + ".txt";  // creates file name from number chosen by user
        if (fileExists(mapFilePath))
            break;
        cout << "File doesn't exist";
    }
    
    // opens map file for reading
    ifstream mapFile(mapFilePath);
    
    // build map vector
    getMapSize(mapFile, mapHeight, mapWidth);  
    getMapVector(mapFile, map); 
    
    while(run){
        string moveOption;
        getGameInfo(map, P);  // update info
        printMap(map);  // print current state of map
        if (!P.alive){
            break;
        }
        
        getline(cin, moveOption);
        editInput(moveOption);
        cout << moveOption << endl;
        break;  // safe exit until the code is updated
    }
    
    mapFile.close();  // close file at end
    
}

bool fileExists(string fileName){  // function to check if a map file exists
    ifstream file(fileName);
    return file.good();
}

void getMapSize(ifstream &mapFile, int &height, int &width){  // function to get map size (height, width)
    string firstLine;
    getline(mapFile, firstLine);
    const int pos = firstLine.find( " " );
    height = stoi(firstLine.substr( 0, pos ));
    width = stoi(firstLine.substr( pos + 3, string::npos ));
}

void getMapVector(ifstream &mapFile, vector <vector <char>> &map){
    int i = 0;
    string currentLine = "";
    while (getline(mapFile,currentLine)){
        vector <char> temp;
        for (int j = 0; j < currentLine.length(); j++) {
            temp.push_back(currentLine[j]);
        }
        map.push_back(temp);
        i++;
    }
    
}

void printMap(vector <vector <char>> map){  //  function to print the map from map vector
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            cout << map.at(i).at(j);
        }
        cout << endl;
    }
}

void getGameInfo(vector <vector <char>> map, Player &P){  // function to get information after last play
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){

            switch(map.at(i).at(j)){
                case 'H':
                    P.x = j;
                    P.y = i;
                    P.alive = true;
                    break;
                case 'h':
                    P.x = j;
                    P.y = i;
                    P.alive = false;
                    break;
                

            }
        }    
    }
}
