// T04_G02

#ifndef MAZE_H
#define MAZE_H  // avoid compiling errors related to redefinition

#include <iostream>
#include <fstream>
#include <sstream> 
#include "Post.hpp"
#include <map>

typedef std::map<Position, Post, MapComparator> mapPost;  // defines a new type of map that accepts Position as key (this one stores Posts as value)

class Maze{
    public:
        Maze();
        void setMazeN(std::string mazeName);
        std::string getMazeN();
        void setDimensions(std::ifstream &maze);
        int getHeight() const;
        int getWidth() const;
        void addPost(Post p);
        void delPost(Position pos);
        mapPost& getPostMap();  
    private:
        std::string mazeN;  // the indication of the maze ("01" or "02" for example)
        int height, width;  // dimensions
        mapPost posts;  // map associating the position of each post as key, and the post itself as value (useful to have direct access to the post at a certain position without looping through every post and checking its position)
};

#endif