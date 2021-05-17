// T04_G02

#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include "Post.hpp"

class Maze{
    public:
        Maze();
        void setFile(std::string name);
        void setDimensions(std::ifstream &map);
        std::string getFileName();
    private:
        std::string mapFile;
        int height, width;
        std::vector <Post> posts;
};