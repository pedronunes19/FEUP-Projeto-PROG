// T04_G02
#include <iostream>
#include <chrono>  // 2 header files included with the purpose of calling a sleep function
#include <thread>
#include <fstream>  // used for file handling
using namespace std;

// declaring functions
void menu();


int main() {
    int menuOption;
    const int TIMESLEEP = 2;
    
    while(true){  // infinite loop to keep the program running until the user wants to stop
        menu();
        cin >> menuOption;
        if (menuOption == 0){  // shuts off the program when the user chooses to exit
            break;
        }
        switch(menuOption){
            case 1:
                cout << "\nThis will be the Rules page" << endl;
                this_thread::sleep_for(chrono::seconds(TIMESLEEP));
                break;
            case 2:
                cout << "\nThe game will be running here" << endl;
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