// T04_G02

#include <iostream>
#include <fstream>
#include <limits>
#include "Game.hpp"

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

void rulesOption(){

}
/**************************************************************************************************************/


/**************************************************************************************************************/
// HELPFUL AUXILIARY FUNCTIONS 
bool fileExists(std::string fileName){
    ifstream file(fileName);
    return file.good();  // if file exists, returns true, otherwise returns false
}

string getMapName(){
    string mapNumber, mapFile;
    bool noFile = true;
    while(noFile){
        cout << "Select which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << endl;
        cin >> mapNumber;
        if (mapNumber == "0"){
            cout << "ainda não sei o que fazer aqui mas tem de voltar ao menu" << endl;  // to be fixed
        }
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(99);
        }
        mapFile = "MAZE_" + mapNumber + ".txt";
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
    string mapName = getMapName();
}