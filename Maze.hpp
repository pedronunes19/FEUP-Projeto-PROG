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
        std::string getMapName();
        void setDimensions(std::ifstream &map);
        int getHeight() const;
        int getWidth() const;
        void addPost(Post p);
        void delPost(int i);
        Post& getPost(int index);  // allow to use individual posts, as well as modify them since they're returned as references
        int getNumberOfPosts() const;
    private:
        std::string mapName;
        int height, width;
        std::vector <Post> posts;
};