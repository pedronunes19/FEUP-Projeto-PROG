// T04_G02

#ifndef GAME_H
#define GAME_H  // avoid compiling errors related to redefinition

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"
#include "gamestructs.hpp"

typedef std::map<Position, Robot, MapComparator> mapRobot;

class Game{
    public:
        Game(const std::string &mapName);  // build game from the map file name
        bool play();  // play the game
        void updateLeaderboards(std::string mazeLeaderboardFile, bool mazeLeaderboard, bool winnersLeaderboard);  /* update (possibly create too) all leaderboards
                                                                                                                second argument signals existance of a leaderboard file (for the map played)
                                                                                                                third argument signals existance of the overall winners file  */
    private:
        // leaderboard
        void organizeLeaderboard(std::string lbPath) const;
        void readEntries(std::string lbPath, std::vector <LbEntry> &entries) const;
        // play
        void setObjectsFromMap(std::ifstream &map);  // to be used once, at the start of each game
        void showDisplay();  // no need to update display (is always up to date)
        Movement moveInput();  // gets the Movement from a valid player movement input (loops until input is accepted)
        void movePlayer();  // everything related to player movement
        void moveRobots();  // everything related to robots movement
        bool validCollision(Robot& robot, Post& post, Position newPos); // check if robot collided with post 
        bool validCollision(Player& player, Robot& robot, Position newPos); // check if human and robot collided 
        bool validCollision(Robot& robot0, Robot& robot1, Position newPos); // check if two robots collided 
        bool validCollision(Player& player, Post& post, Position newPos); // check if human collided with post (any type)
        bool gameOver();  // verify end of game conditions and set gameResult if needed
    private:
        Maze maze;  // the maze corresponding to the game
        Player player; // the player
		mapRobot robots;  // map containing every position with a robot, paired together with the robot itself
        int timePlayed;  // time score to use on leaderboards
        bool gameResult;  // value to be returned by play()

};

#endif