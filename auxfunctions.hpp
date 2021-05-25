// T04_G02

#ifndef FUNCTIONS_H
#define FUNCTIONS_H  // avoid compiling errors related to redefinition

#include <iostream>
#include <fstream>
#include <limits>
#include "Game.hpp"

void deleteWinners(){  // to be used at exit (more explanation on it's purpose on main.cpp)
    remove("winners.txt");
}

/**************************************************************************************************************/
// PRINTING FUNCTIONS
void menu(){  // function to draw menu to the screen
    std::cout << "-----------------------------------------------------\n"
              << "                     ROBOTS GAME                     \n"
              << "                                                     \n"
              << "                      1) Rules                       \n"
              << "                      2) Play                        \n"
              << "                      0) Exit                        \n"
              << "                                                     \n"
              << "               Select your option: ";         
}

void rulesOption(bool &programExecuting){
    string line, exitRules;
    ifstream rules("RULES.txt");
    while(getline(rules, line)){
        std::cout << line << endl;
    }
    rules.close();  // close stream once rules have been displayed
    getline(cin, exitRules);  // wait for user input to return to menu
    if (cin.eof())     // CTRL-Z/CTRL-D 
        programExecuting = false;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// HELPFUL AUXILIARY FUNCTIONS 
bool fileExists(std::string fileName){
    ifstream file(fileName);
    return file.good();  // if file exists, returns true, otherwise returns false
}

string getMapNameStart(){
    string mapNumber, mapFile;
    bool noFile = true;
    while(noFile){  // run loop until a valid file name is found
        cout << "Select which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << endl;
        cin >> mapNumber;
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (mapNumber == "0"){  // go back to menu
            cout << "ainda não sei o que fazer aqui mas tem de voltar ao menu" << endl;  // to be fixed
        }
        mapFile = "MAZE_" + mapNumber + ".txt";  // creates file name from number chosen by user
        if (fileExists(mapFile)){
            noFile = false;
            continue;
        }
        cout << "That map doesn't exist" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer   
    }
    return mapFile;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// PLAY FUNCTION (REFLECTS THE PLAY OPTION OF THE MENU)
void playOption(){
    string mapNameInput = getMapNameStart();  // get the file name to be used for this game
    Game robotgame(mapNameInput);  // build the Game object
    bool gameResult = robotgame.play();  // this initilazation will run the game, and store the result (win or lost) right after
    if (gameResult){  
        int pos = mapNameInput.find('.');
        string mapLeaderboardName = mapNameInput.substr(0, mapNameInput.length() - pos) + "_WINNERS.txt";  // create name of leaderboard file (map exclusive)
        robotgame.updateLeaderboards(mapLeaderboardName, fileExists(mapLeaderboardName), fileExists("winners.txt"));
    }
    else{
        cout << "You lost. Try again" << endl;  // end message if player loses, after this go back to menu
    }
}

#endif