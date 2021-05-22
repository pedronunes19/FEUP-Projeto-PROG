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
                this->player = Player(x,y);
            }
            if (temp == 'R'){
                robots.push_back(Robot(x,y));
            }
            if (temp == '*' || temp == '+' || temp == 'O'){
                Post p(x, y, temp);
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



bool Game::collide(Robot& robot, Post& post) const{
    return (robot.getPos() == post.getPos());
}

bool Game::collide(Robot& robot, Player& player) const{
    return (robot.getPos() == player.getPos());
}

bool Game::collide(Robot& robot0, Robot& robot1) const
{
    return (robot0.getPos()==robot1.getPos());
}

bool Game::collide(Player& player, Post& post) const
{
    return (player.getPos()==post.getPos());
}
