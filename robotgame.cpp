// T04_G02
#include <iostream>
#include <chrono>  // can handle with time
#include <thread>
#include <fstream>  // used for file handling
using namespace std;

// declaring functions
void menu();
void rules(bool &programExecuting);
void play(bool &programExecuting);
bool fileExists(string fileName);
void getMapSize(string firstLine, int &height, int &widht);
void getMapArray(ifstream mapFile);

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
                this_thread::sleep_for(chrono::seconds(TIMESLEEP));
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

void rules(bool &programExecuting){  // function to display rules
    char exitRules;
    cout << "\nThis will be the Rules page (press any character to return to the menu) ";
    cin >> exitRules;  // wait for user input to return to menu
    if (cin.eof())     // more CTRL-Z CTRL-D stuff
        programExecuting = false;

}

void play(bool &programExecuting){  // function to play the game
    string mapNumber, mapFilePath, firstLine, currentLine;
    bool noFile = true;  // loop variable for file check
    int mapHeight, mapWidth;  // map dimensions
    while(noFile){
        cin.ignore(1);  // cleans input allowing getline() to wait for input
        cout << "\nSelect which map you would like to play (ex. 01, 02, ..., 99): " << endl;    
        getline(cin, mapNumber);
        mapFilePath = "MAZE_" + mapNumber + ".txt";  // creates file name from number chosen by user
        if (fileExists(mapFilePath))
            break;
        cout << "File doesn't exist";
    }
    
    ifstream mapFile(mapFilePath); // opens map file for reading
    
    getline(mapFile, firstLine);
    getMapSize(firstLine, mapHeight, mapWidth);

    string map[mapHeight][mapWidth]; // creates map array
}

bool fileExists(string fileName){
    ifstream file(fileName);
    return file.good();
}

void getMapSize(string firstLine, int &height, int &width){  // 
    const int pos = firstLine.find( " " );
    height = stoi(firstLine.substr( 0, pos ));
    width = stoi(firstLine.substr( pos + 3, string::npos ));
}

void getMapArray(ifstream mapFile){
    string currentLine = "";
    while (getline(mapFile,currentLine)){

    }
    
}