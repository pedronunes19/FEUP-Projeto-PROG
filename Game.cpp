// T04_G02

#include "Game.hpp"

using namespace std;

Game::Game(const string &mapName){
    maze.setMapName(mapName);  // sets the maze with the file name for future use
    ifstream map(mapName);  // open stream to read everything from file
    maze.setDimensions(map);  // store maze dimensions
    maze.setMapDisplay(map);  // stores the maze in the 2d char vector

    // create all other objects (player, robots, posts (insert in maze), exits (to be defined))
    for (int y = 0; y < maze.getHeight(); y++){
        for (int x = 0; x < maze.getWidth(); x++){
            char temp = maze.getChar(x, y);
            if (temp == 'H'){
                // store coordinates for player
            }
            if (temp == 'R'){
                // store coordinates for robot and append to robots vector
            }
            if (temp == '*' || temp == '+'){
                Post p(temp, x, y);
                maze.addPost(p);
            }
            if (temp == 'O'){
                // how to store exits is still to be defined
            }
        }
    }

}

bool Game::play(){
    auto gameStart = chrono::steady_clock::now();  // starts clock to count gametime
    // lots of gameplay here
    auto gameEnd = chrono::steady_clock::now();  // time when game is over   
    this -> time = chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count();  // full time played
}


