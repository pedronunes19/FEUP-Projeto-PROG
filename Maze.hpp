// T04_G02

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include "Post.hpp"

class Maze{
    public:
        Maze();
        Maze(std::string mapName);
        void setDimensions(std::ifstream &map);
        void setMapVector(std::ifstream &map);
        std::string getMapName();
        int getHeight() const;
        int getWidth() const;
        char getChar(int x, int y);
        void addPost(Post p);
    private:
        std::string mapName;
        int height, width;
        std::vector <std::vector <char>> mapVector;
        std::vector <Post> posts;
};