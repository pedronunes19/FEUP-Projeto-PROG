// T04_G02

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <chrono>
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"

class Game{
    public:
        Game(const std::string &mapName);  // build game from the map file name
        bool play();  // play the game
    private:
        void setObjectsFromMap(std::ifstream &map);  // to be used once, at the start of each game
        void showDisplay() const;  // no need to update display (is always up to date)
        bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
        bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
        bool collide(Robot& robot0, Robot& robot1); // check if two robots collided (and possibly set both as dead/stuck)
        bool collide(Post& post, Player& player); // check if human collided with post (and possibly set human as dead), will be used also for testing if the player meets the exit
    private:
        Maze maze;
        Player player;
        std::vector <Robot> robots;
        int timePlayed;

};