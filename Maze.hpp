// T04_G02

#ifndef MAZE_H
#define MAZE_H  // avoid compiling errors related to redefinition

#include <iostream>
#include <fstream>
#include <sstream> 
#include "Post.hpp"
#include <map>

using namespace std;

class Maze{
    public:
        Maze();
        void setMapN(std::string mapName);
        std::string getMapN();
        void setDimensions(std::ifstream &map);
        int getHeight() const;
        int getWidth() const;
        void addPost(Post p);
        void delPost(int i);
        Post& getPost(int index);  // allow to use individual posts, as well as modify them since they're returned as references
        int getNumberOfPosts() const;
    private:
        std::string mapN;
        int height, width;
        map <Position,Post> posts;
};

#endif