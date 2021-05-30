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
        void setMazeN(std::string mazeName);  // stores the number of the maze inside it's object to be able to use this information inside the game
        std::string getMazeN();  // returns the number of the maze
        void setDimensions(std::ifstream &maze);  //set height and width of the maze
        int getHeight() const;  // return height
        int getWidth() const;  // return width
        void addPost(Post p);  // store a new post inside the maze  object
        void delPost(Position pos);  // delete a post from maze object (when a robot or the player are killed on top of the post)
        mapPost& getPostMap();  // access the posts from the game, although it´s not best practice to access a private member outside of the class, we felt like it would make collision handling a lot easier, and since Maze and Game are supposed to be used together this shouldn't be a such big issue
    private:
        std::string mazeN;  // the indication of the maze ("01" or "02" for example)
        int height, width;  // dimensions
        mapPost posts;  // map associating the position of each post as key, and the post itself as value (useful to have direct access to the post at a certain position without looping through every post and checking its position)
};

#endif