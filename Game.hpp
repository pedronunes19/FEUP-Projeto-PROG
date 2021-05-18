// T04_G02

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include "Maze.hpp"
#include "Player.hpp"
#include "Robot.hpp"

class Game{
    public:
        Game(const std::string &mapName);
    private:
        Maze maze;
        Player player;
        std::vector <Robot> robots;

};