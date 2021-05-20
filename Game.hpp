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
        void showDisplay() const;
        // possibly a clearDisplay() to remove player and robots from maze's mapDisplay while we have their position before moving 
        void updateDisplay();  // update the display of the maze after every full play
        bool collide(Robot& robot, Post& post); // check if robot collided with post (and possibly set it as dead)
        bool collide(Robot& robot, Player& player); // check if human and robot collided (and possibly set human as dead)
        bool collide(Robot& robot0, Robot& robot1); // check if two robots collided (and possibly set both as dead/stuck)
        bool collide(Post& post, Player& player); // check if human collided with post (and possibly set human as dead)
        // probably a collide with player and exit will be added
    private:
        Maze maze;
        Player player;
        std::vector <Robot> robots;
        int time;

};