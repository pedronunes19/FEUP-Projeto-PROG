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
        Game();
        bool fileExists(std::string fileName) const;
        std::string getMapName() const;  // handle input of map number and return map file name
        void buildMaze();  // build maze object
    private:
        Maze maze;
        Player player;
        std::vector <Robot> robots;

};