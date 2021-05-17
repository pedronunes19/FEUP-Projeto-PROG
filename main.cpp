// T04_G02

#include "Game.hpp"
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"




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
            const int safeNumber = 999;
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
                // rules();                                
                break;
            case 2:                                                     // Play (starts game)
                // play();
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

