// T04_G02

#ifndef FUNCTIONS_H
#define FUNCTIONS_H  // avoid compiling errors related to redefinition

#include "Game.hpp"


/**************************************************************************************************************/
// HELPFUL AUXILIARY FUNCTIONS 
bool fileExists(std::string fileName){  // function to check existance of a file (returns true if it exists, false otherwise)
    std::ifstream file(fileName);
    return file.good();  // if file exists, returns true, otherwise returns false
}

std::string getMapNameStart(){  // function to be used before the game to get the map name from user input
    std::string mapNumber, mapFile;
    bool noFile = true;
    while(noFile){  // run loop until a valid file name is found
        std::cout << "Select which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << std::endl;
        std::cin >> mapNumber;
        if (std::cin.eof()){  // end with CTRL-Z/CTRL-D
            std::cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (mapNumber == "0"){  // go back to menu
            return "BACK TO MENU";
        }
        mapFile = "MAZE_" + mapNumber + ".txt";  // creates file name from number chosen by user
        if (fileExists(mapFile)){
            noFile = false;
            continue;
        }
        std::cout << "That map doesn't exist" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // remove the rest of the line from input buffer   
    }
    return mapFile;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// PRINTING FUNCTIONS
void menu(){  // function to draw menu to the screen
    std::cout << "-----------------------------------------------------\n"
              << "                     ROBOTS GAME                     \n"
              << "                                                     \n"
              << "                      1)  Rules                      \n"
              << "                      2)  Play                       \n"
              << "                      3)  Winners                    \n"
              << "                      0)  Exit                       \n"
              << "                                                     \n"
              << "               Select your option: ";         
}

void rulesOption(bool &programExecuting){  // function to print the rules (from RULES.txt)
    std::cout << std::endl;  // format output (separate menu from option output)
    std::string line, exitRules;
    std::ifstream rules("RULES.txt");
    while(getline(rules, line)){
        std::cout << line << std::endl;
    }
    rules.close();  // close stream once rules have been displayed
    getline(std::cin, exitRules);  // wait for user input to return to menu
    if (std::cin.eof())     // CTRL-Z/CTRL-D 
        programExecuting = false;
}

void winnersOption(bool &programExecuting){  // function to print the winners leaderboard (or "There aren't any winners yet" if it does not exist) + alows user to reset leaderboard
    std::cout << std::endl;  // format output (separate menu from option output)
    std::string exitWinners;
    if (fileExists("winners.txt")){
        std::string line;
        std::ifstream winners("winners.txt");
        while(getline(winners, line)){
            std::cout << line << std::endl;
        }
        winners.close();  // close stream once winners have been displayed
    }
    else{  // if there is no leaderboard to show, user can quit without RESET option
        std::cout << "There aren't any winners yet" << std::endl;
        std::cout << "Press anything when you're ready to leave: ";
        getline(std::cin, exitWinners);
        return;
    }

    std::cout << "Press anything when you're ready to leave (write 'RESET' if you want to reset the leaderboard, deleting the current one): ";
    std::cin >> exitWinners;  // wait for user input to return to menu
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // remove the rest of the line from input buffer

    if (std::cin.eof()){  // CTRL-Z/CTRL-D 
        std::cout << "Program terminated with CTRL-Z or CTRL-D";
        programExecuting = false;
    }
    if (exitWinners == "RESET"){  // in case user wants to reset leaderboard
        // confirm DELETE
        char confirmation;
        std::cout << "Are you sure? You won't be able see this data inside the game anymore ('y'/'Y' to confirm): ";
        std::cin >> confirmation;
        if (std::cin.eof()){  // CTRL-Z/CTRL-D 
            std::cout << "Program terminated with CTRL-Z or CTRL-D";
            programExecuting = false;
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // remove the rest of the line from input buffer
        std::cin.clear();
        if (tolower(confirmation) == 'y')
            remove("winners.txt");  // delete the file that contains the leaderboard (maze leaderboards remain untouched)
    }
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// PLAY FUNCTION (REFLECTS THE PLAY OPTION OF THE MENU)
void playOption(){
    std::string mapNameInput = getMapNameStart();  // get the file name to be used for this game
    if (mapNameInput == "BACK TO MENU"){
        return;
    }
    Game robotgame(mapNameInput);  // build the Game object
    bool gameResult = robotgame.play();  // this initilazation will run the game, and store the result (win or lost) right after
    if (gameResult){  
        int pos = mapNameInput.find('.');
        std::string mapLeaderboardName = mapNameInput.substr(0, pos) + "_WINNERS.txt";  // create name of leaderboard file (map exclusive)
        robotgame.updateLeaderboards(mapLeaderboardName, fileExists(mapLeaderboardName), fileExists("winners.txt"));
        std::cout << "Congratulations on beating the game, check how you did with option 3 of the menu" << std::endl;
    }
    else{
        std::cout << "You lost. Try again" << std::endl;  // end message if player loses, after this go back to menu
    }
}
/**************************************************************************************************************/

#endif