// T04_G02

#include "Game.hpp"

using namespace std;

Game::Game(const string &mapName){
    maze.setMapName(mapName);  // sets the maze with the file name for future use
    ifstream map(mapName);  // open stream to read everything from file
    maze.setDimensions(map);  // store maze dimensions
    setObjectsFromMap(map);
    map.close(); // close stream (map file won't be touched after this)
}

void Game::setObjectsFromMap(std::ifstream &map){
    std::string currentLine;
    int y = 0;
    while (getline(map,currentLine)){  // reads line by line
        for (int x = 0; x < currentLine.length(); x++) {  // read every character in the line 
            char temp = currentLine[x];
            if (temp == 'H'){
                // store coordinates for player
            }
            if (temp == 'R'){
                // store coordinates for robot and append to robots vector
            }
            if (temp == '*' || temp == '+' || temp == 'O'){
                Post p(temp, x, y);
                maze.addPost(p);
            }
        }
    y++;
    }
}

bool Game::play(){
    auto gameStart = chrono::steady_clock::now();  // starts clock to count gametime
    // lots of gameplay here
    auto gameEnd = chrono::steady_clock::now();  // time when game is over   
    this -> timePlayed= chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count();  // full time played
}


