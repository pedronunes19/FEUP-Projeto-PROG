// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"

/**************************************************************************************************************/
// CONSTRUCTORS
Maze::Maze(){
    // default constructor
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// SET METHODS
void Maze::setMazeN(std::string mazeName){
    int pos = mazeName.find('_');
    int pos1 = mazeName.find('.');
    this -> mazeN = mazeName.substr(pos+1, pos1 - pos - 1);
}


void Maze::setDimensions(std::ifstream &maze){  // uses the first line of the file to read dimensions + removes that line from filestream
    std::string firstLine;
    getline(maze, firstLine);
    std::stringstream ss;
    ss << firstLine;
    char aux;
    ss >> height >> aux >> width;
}
/**************************************************************************************************************/

/**************************************************************************************************************/
// GET INFO
std::string Maze::getMazeN(){
    return mazeN;
}

int Maze::getHeight() const{
    return height;
}

int Maze::getWidth() const{
    return width;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// POSTS

void Maze::addPost(Post p){  // add a Post to the the posts data structure
    this->posts.insert(std::pair<Position, Post>(p.getPos(),p));
}

void Maze::delPost(Position pos){  // delete Post at a Position (works fine because there can never be 2 posts on the same position)
    this->posts.erase(posts.find(pos));
}

mapPost& Maze::getPostMap(){  // get full data structure for posts
    return posts;
}

/**************************************************************************************************************/