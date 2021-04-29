// T04_G02
#include <iostream>
#include <algorithm> // used to call std::sort
#include <iomanip>
#include <chrono>  // used to handle time
#include <fstream>  // used to handle files
#include <vector>
#include "gamestructs.hpp"  // contains structs created for the game
#include <limits>  // used with cin.ignore()
using namespace std;

// declaring functions
void menu();
void editInput(string &input);
void rules(bool &programExecuting);
void play(bool &programExecuting);
bool fileExists(string fileName);
void getMapVector(ifstream &mapFile, vector <vector <char>> &map, Player &P, vector <Robot> &robots);
void readInfo(int x, int y, char aux, Player &P, vector <Robot> &robots, int &id);
void printMap(const vector <vector <char>> map);
void movePlayer(vector <vector <char>>& map, Player &P);
void moveRobots(vector <vector <char>>& map, vector <Robot> &robots, Player &P);
bool allRobotsDead(const vector <Robot> &robots);
void updateLeaderboard(string number, int time, bool &run, bool &programExecuting);
void organizeLeaderboard(string lbPath);
void readEntries(string lbPath, vector <LbEntry> &entries);
bool compare(const LbEntry i1, const LbEntry i2);


int main() {
    bool programExecuting = true;
    
    while(programExecuting){  // "infinite" loop to keep the program running until the user wants to stop
        int menuOption;
        menu();  // display starting menu
        cin >> menuOption;
        if (cin.eof()){  // closes program with CTRL-Z (Windows) or CTRL-D (Linux)
            break;
        }
        if (cin.fail()){  // avoids error if input is not an integer
            const int safeNumber = 3;
            cin.clear();
            menuOption = safeNumber;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer
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
            default:                                                    // In case no valid option is selected
                cout << "\nPlease choose a valid option" << endl;
        }   
    }
    return 0;
}

void menu(){  // function to draw menu to the screen
    cout << "-----------------------------------------------------\n"
         << "                     ROBOTS GAME                     \n"
         << "                                                     \n"
         << "                      1) Rules                       \n"
         << "                      2) Play                        \n"
         << "                      0) Exit                        \n"
         << "                                                     \n"
         << "               Select your option: ";         
}

void editInput(string &input){  // function to edit the user input, only considering what is written before any space
    int pos = input.find(' ');
    input = input.substr(0, pos);
}

void rules(bool &programExecuting){  // function to display rules
    string exitRules;
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
         << "\n- Time is shown in seconds"
         << "\nInput:"
         << "\n- The program reads only the first character when typing the movement or the menu option"
         << "\n- When reading map number some user input may be neglected to avoid issues (for example when reading file name, '01', '01  ' and '01  5' are all considered by the program as '01')"
         << "\nPress any character when you're ready to leave -> ";
    getline(cin, exitRules);  // wait for user input to return to menu
    if (cin.eof())     // CTRL-Z/CTRL-D 
        programExecuting = false;
}

void play(bool &programExecuting){  // function to play the game
    string mapNumber, mapFilePath, firstLine, currentLine;
    bool noFile = true;  // variable for file check
    bool run = true;  // variable to keep game going
    vector <vector <char>> map;  // map stored in a vector
    struct Player P;  // declaring the player as a Player struct
    vector <Robot> robots;  // vector that will contain robots as Robot structs

    // run loop until a existing file is found
    while(noFile){ 
        cout << "\nSelect which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << endl;    
        getline(cin, mapNumber);
        editInput(mapNumber);
        if (mapNumber == "0"){  // back to menu
            return;
        }
        if (cin.eof()){  // CTRL-Z/CTRL-D
            programExecuting = false;
            return;
        }
        mapFilePath = "MAZE_" + mapNumber + ".txt";  // creates file name from number chosen by user
        if (fileExists(mapFilePath)){  // break the loop and move into the game
            cout << "Playing map " << mapNumber << "!" << endl;
            break;
        }
        cout << "File doesn't exist";
    }
    
    // opens map file for reading
    ifstream mapFile(mapFilePath);
    
    // build map vector and get all information needed 
    mapFile.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore the first line containing the map dimensions (will not be used)
    getMapVector(mapFile, map, P, robots); 

    // starts clock to count gametime
    auto gameStart = chrono::steady_clock::now();

    while(run){
        printMap(map);  // print current state of map
        if (!P.alive){  // end the game if the player loses
            cout << "You lost" << endl;
            break;
        }
        if (allRobotsDead(robots)){  // condition met for win
            cout << "You win" << endl;
            auto gameEnd = chrono::steady_clock::now();  // time when game is over                                                                          
            updateLeaderboard(mapNumber, chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count(), run, programExecuting); 
            break;
        }
        
        movePlayer(map, P);  // move player according to input
        
        // stop program (CTRL+Z)
        if (cin.eof()){
            programExecuting = false;
            break;
        }
        moveRobots(map, robots, P);  // move robots towards player
    }

    mapFile.close();  // close file at the end of the game
}

bool fileExists(string fileName){  // function to check if a map file exists
    ifstream file(fileName);
    return file.good();  // if file exists, returns true, otherwise returns false
}


void getMapVector(ifstream &mapFile, vector <vector <char>> &map, Player &P, vector <Robot> &robots){  // function to read map from file to vector (readInfo() executed inside)
    int i = 0;
    string currentLine = "";
    int robotId = 1;  // this variable will correspond to a robot's id, when a robot is found (will be incremented when that happens)
    while (getline(mapFile,currentLine)){  // reads line by line
        vector <char> temp;
        for (int j = 0; j < currentLine.length(); j++) {  // read every character in the line 
            char aux = currentLine[j];
            temp.push_back(aux);  // add the caracter to the vector that contains the line
            readInfo(j, i, aux, P, robots, robotId);  // get important information from character (if there is any)
        }
        map.push_back(temp);  // push the vector created with the line to map 
        i++;
    } 
}

void readInfo(int x, int y, char aux, Player &P, vector <Robot> &robots, int &id){  // function to read a character and get important information
    switch(aux){ 
        case 'H':                      // info of player
            P.x = x;
            P.y = y;
            P.alive = true;
            break;
        case 'R':                      // info of robot
            robots.push_back(Robot());
            int last = robots.size() - 1;
            robots[last].x = x;
            robots[last].y = y;
            robots[last].id = id;
            robots[last].alive = true;
            id++;
    }    
}

void printMap(const vector <vector <char>> map){  //  function to print the map from map vector
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            cout << map.at(i).at(j);
        }
        cout << endl;
    }
}

void movePlayer(vector <vector <char>>& map, Player &P){  // function to do everything related to moving the player
    int direction[2];
    char temp, move;
    const string VALIDMOVES = "qweasdzxc";  // string containing every char correponding to a valid move
    string moveOption;
    bool valid;

    do{
        valid = true;
        cout << "Move -> ";
        cin >> move;
        if (cin.eof())  // CTRL-Z/CTRL-D
            return;
        if (cin.fail()){  // staying as a safety measure
            cin.clear();
            valid = false;
            cout << "Invalid move, choose another direction" << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer
        move = tolower(move);  // avoid case sensitivity
        
        if (move == 'e' || move == 'd' || move == 'c') direction[0] = 1;        // define direction on x axis
        else if (move == 'q' || move == 'a' || move == 'z') direction[0] = -1;
        else direction[0] = 0;

        if (move == 'z' || move == 'x' || move == 'c') direction[1] = 1;        // define direction on y axis
        else if (move == 'q' || move == 'w' || move == 'e') direction[1] = -1;
        else direction[1] = 0;

        if(map[P.y + direction[1]][P.x + direction[0]] == 'r' || VALIDMOVES.find(move) == string::npos){  //Check if new position is occupied by a dead robot or if the character that specifies the direction is invalid
            valid = false;
            cout << "Invalid move, choose another direction" << endl;
        }

    }while(!valid);

    map[P.y][P.x] = ' ';
    P.x += direction[0];
    P.y += direction[1];
    temp = map[P.y][P.x];

    if (temp == ' ') map[P.y][P.x] = 'H';  // regular move
    else {
        map[P.y][P.x] = 'h';  // player dies
        P.alive = false;
    }
}


void moveRobots(vector <vector <char>>& map, vector <Robot> &robots, Player &P){  // function to move robots according to player position
    char temp;
    int direction[2];

    for (int i = 0; i < robots.size(); i++){
        if (!P.alive)
            return;
        
        if (!robots[i].alive){  //skip iteration if robot is dead
            continue; 
        }
        if (map[robots[i].y][robots[i].x] == 'r'){  //skip iteration if robot gets "hit" by any robot that previously moved to it's position
            robots[i].alive = false;
            continue;
        }

        if(robots[i].x < P.x) direction[0] = 1;        // define direction on x axis
        else if (robots[i].x > P.x) direction[0] = -1;
        else direction[0] = 0;

        if(robots[i].y < P.y) direction[1] = 1;        // define direction on y axis
        else if (robots[i].y > P.y) direction[1] = -1;
        else direction[1] = 0;

        map[robots[i].y][robots[i].x] = ' ';
        robots[i].x += direction[0];
        robots[i].y += direction[1];
        temp = map[robots[i].y][robots[i].x];

        if (temp == ' ') map[robots[i].y][robots[i].x] = 'R';  // regular move
        else if (temp == '*' || temp == 'R' || temp == 'r'){  // robot gets stuck/dead
            map[robots[i].y][robots[i].x] = 'r';
            robots[i].alive = false;
        }
        else{
            map[robots[i].y][robots[i].x] = 'h';  // robot kills player
            P.alive = false;
            return;
        }
    }
}

bool allRobotsDead(const vector <Robot> &robots){  // function to check if there is any functional robot 
    for (int i = 0; i < robots.size(); i++){
        if (robots[i].alive == true) return false;
    }
    return true;
}

void updateLeaderboard(string number, int time, bool &run, bool &programExecuting){  // function to deal with leaderboards (create or update)
    string leaderboardFile = "MAZE_" + number + "_WINNERS.txt";  // file name for leaderboard created from file number
    string playerName;
    bool emptyName = true;

    // create leaderboard file if it doesn't already exist
    if (!fileExists(leaderboardFile)){
        ofstream leaderboard(leaderboardFile);
        leaderboard << "Player          - Time" << endl << "----------------------" << endl;  // write basic leaderboard template
        leaderboard.close();
    }
    // store the player's name
    const int MAXNAMELENGTH = 15;
    while (emptyName){
        cout << "Write your name here (max 15 characters): ";
        getline(cin, playerName);
        if (cin.eof()){  // CTRL-Z/CTRL-D
            run = false;
            programExecuting = false;
            return;
        }
        if (playerName.length() > 0){
            if (playerName.length() > MAXNAMELENGTH){  // cut name at character limit
                playerName = playerName.substr(0, MAXNAMELENGTH);
            }
            else{
                for (int i = playerName.length(); i < MAXNAMELENGTH; i++){  
                    playerName += ' ';  // fill with spaces to fit 15 characters (fits the table better than setw())
                }
            }
            break;
        }
        cout << "You have to choose a name!" << endl;
    }

    // write the name and time to the file
    ofstream leaderboard;
    leaderboard.open(leaderboardFile, ios::app);
    leaderboard << playerName << " - " << time << endl;
    leaderboard.close();

    // organize leaderboard
    organizeLeaderboard(leaderboardFile);
}

void readEntries(string lbPath, vector <LbEntry> &entries){  // function to read leaderboard entries (name, time)
    ifstream lbFile(lbPath);   // open leaderboard file for reading
    string currentLine;
    const int NAMELENGTH = 18;
    
    // skip first 2 lines
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while(getline(lbFile, currentLine)){
        LbEntry currentEntry;

        // store entries
        currentEntry.name = currentLine.substr(0, NAMELENGTH);
        currentEntry.time = stoi(currentLine.substr(NAMELENGTH, string::npos - 1));
        entries.push_back(currentEntry);
    }
    lbFile.close();  // close file after reading
}

bool compare(const LbEntry i1, const LbEntry i2){  // function to compare leaderboard times (to be used with std::sort)
        return (i1.time < i2.time);
    }

void organizeLeaderboard(string lbPath){  // function to organize (sort) the leaderboard
    vector <LbEntry> entries;  // vector to store leaderboard entries
    readEntries(lbPath, entries);  // read all entries
    ofstream lbFile(lbPath);
    lbFile << "Player          - Time" << endl << "----------------------" << endl;  // write the first 2 lines back to file

    sort(entries.begin(), entries.end(), compare);  // sort entries vector by time
    for(int i = 0; i < entries.size(); i++) {
        lbFile << entries[i].name << entries[i].time << endl;
    }
    lbFile.close();  // close file after writing ordered leaderboard to file
}