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
        void showDisplay() const;  // no need to update display (is always up to date)
        void movePlayer();
        void moveRobots();
        bool collide(Robot& robot, Post& post) const; // check if robot collided with post 
        bool collide(Robot& robot, Player& player) const; // check if human and robot collided 
        bool collide(Robot& robot0, Robot& robot1) const; // check if two robots collided 
        bool collide(Player& player, Post& post) const; // check if human collided with post, will be used also for testing if the player meets the exit
    private:
        Maze maze;
        Player player;
        vector <Robot> robots;
        int timePlayed;

};