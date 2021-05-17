// T04_G02

#include "Game.hpp"
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"

using namespace std;

Game::Game(){
    // default constructor
}

bool Game::fileExists(std::string fileName) const{
    ifstream file(fileName);
    return file.good();  // if file exists, returns true, otherwise returns false
}

string Game::getMapName() const {
    string mapNumber, mapFile;
    bool noFile = true;
    while(noFile){
        cout << "Select which map you would like to play (ex. 01, 02, ..., 99) or 0 to go back to the menu: " << endl;
        cin >> mapNumber;
        if (mapNumber == "0"){
            return "ainda não sei o que fazer aqui mas tem de voltar ao menu";  // to be fixed
        }
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(1);
        }
        mapFile = "MAZE_" + mapNumber + ".txt";
        if (fileExists(mapFile)){
            return mapFile;
        }
        cout << "That map doesn't exist" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer

    }
}

void Game::buildMaze(){
    string name = getMapName();
    this -> maze.setFile(name);
    ifstream map(maze.getFileName());
    this -> maze.setDimensions(map);


    map.close();  // close file after the map is built
}