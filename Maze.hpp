// T04_G02

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include "Post.hpp"

class Maze{
    public:
        Maze();
        void setMapName(std::string mapName);
        void setDimensions(std::ifstream &map);
        void setMapDisplay(std::ifstream &map);
        std::string getMapName();
        int getHeight() const;
        int getWidth() const;
        char getChar(int x, int y);
        void addPost(Post p);
    private:
        std::string mapName;
        int height, width;
        std::vector <std::vector <char>> mapDisplay;
        std::vector <Post> posts;
};