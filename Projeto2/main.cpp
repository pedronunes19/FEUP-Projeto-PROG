// T04_G02

#include "auxfunctions.hpp"

using namespace std;

int main() {
    bool programExecuting = true;
    
    while(programExecuting){  // "infinite" loop to keep the program running until the user wants to stop
        int menuOption;
        menu();  // display starting menu
        cin >> menuOption;
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (cin.fail()){  // avoids error if input is not an integer
            const short int safeNumber = 4;
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
                rulesOption(programExecuting);                                
                break;
            case 2:                                                     // Play (starts game)
                playOption();
                break;
            case 3:                                                     // Winners (displays every player that has beaten the game, if there is any)
                winnersOption(programExecuting);
                break;
            default:                                                    // In case no valid option is selected
                cout << "\nPlease choose a valid option" << endl;
        }   
    }
    return 0;
}


