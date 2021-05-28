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
        void setMapN(std::string mapName);
        std::string getMapN();
        void setDimensions(std::ifstream &map);
        int getHeight() const;
        int getWidth() const;
        void addPost(Post p);
        void delPost(Position pos);
        mapPost& getPostMap();
        Post& getPost(Position pos);  // allow to use individual posts, as well as modify them since they're returned as references
        int getNumberOfPosts() const;
    private:
        std::string mapN;  // the indication of the maze ("01" or "02" for example)
        int height, width;  // dimensions
        mapPost posts;  // map containing every position with a post, paired together with the post itself
};

#endif