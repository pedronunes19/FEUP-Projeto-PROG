// T04_G02
#include <iostream>
#include <chrono>  // 2 header files included with the purpose of calling a sleep function (might be removed later)
#include <thread>
#include <fstream>  // used for file handling
using namespace std;

// declaring functions
void menu();
void rules();
void play();


int main() {
    bool programExecuting = true;
    int menuOption;
    const int TIMESLEEP = 2;  // sleep functions are being used for tests purpose
    
    while(programExecuting){  // infinite loop to keep the program running until the user wants to stop
        menu();
        cin >> menuOption;
        switch(menuOption){
            case 0:
                programExecuting = false;
                break;
            case 1:
                rules();
                this_thread::sleep_for(chrono::seconds(TIMESLEEP));
                break;
            case 2:
                play();
                this_thread::sleep_for(chrono::seconds(TIMESLEEP));
                break;
            default:
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
         << "             Select you option: ";         
}

void rules(){  // function to display rules
    cout << "\nThis will be the Rules page" << endl;
}

void play(){  // function to play the game
    cout << "\nThe game will be running here" << endl;
}