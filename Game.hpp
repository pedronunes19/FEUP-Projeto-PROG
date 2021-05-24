// T04_G02

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <chrono>
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"

using namespace std;

class Game{
    public:
        Game(const string &mapName);  // build game from the map file name
        bool play();  // play the game
    private:
        void setObjectsFromMap(ifstream &map);  // to be used once, at the start of each game
        void showDisplay();  // no need to update display (is always up to date)
        Movement moveInput();  // gets the Movement from a valid player movement input (loops until input is accepted)
        void movePlayer();  // everything related to player movement
        void moveRobots();  // everything related to robots movement
        bool valid_move(Robot& robot, int postIndex, Movement mov); // check if robot collided with post 
        bool valid_move(Player& player, Robot& robot, Movement mov); // check if human and robot collided 
        bool valid_move(Robot& robot0, Robot& robot1, Movement mov); // check if two robots collided 
        bool valid_move(Player& player, Post& post, Movement mov); // check if human collided with post (any type)
        void playerExits();  // signals that the player has found an exit
    private:
        Maze maze;  // the maze corresponding to the game
        Player player;
        vector <Robot> robots;
        int timePlayed;  // time score to use on leaderboards
        bool playerExited;

};