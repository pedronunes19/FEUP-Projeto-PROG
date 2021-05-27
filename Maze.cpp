// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"


Maze::Maze(){
    // default constructor
}

/**************************************************************************************************************/
// SET METHODS
void Maze::setMapN(std::string mapName){
    int pos = mapName.find('_');
    int pos1 = mapName.find('.');
    std::string mapN = mapName.substr(pos+1, pos1 - pos);
    this -> mapN = mapN;
}


void Maze::setDimensions(std::ifstream &map){  // uses the first line of the file to read dimensions + removes that line from filestream
    std::string firstLine;
    getline(map, firstLine);
    std::stringstream ss;
    ss << firstLine;
    char aux;
    ss >> height >> aux >> width;
}
/**************************************************************************************************************/

/**************************************************************************************************************/
// GET INFO
std::string Maze::getMapN(){
    return this->mapN;
}


int Maze::getHeight() const{
    return this->height;
}

int Maze::getWidth() const{
    return this->width;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// POSTS
int Maze::getNumberOfPosts() const{
    return this->posts.size();
}

void Maze::addPost(Post p){  // add a Post to the the posts data structure
    this->posts.insert(std::pair<Position, Post>(p.getPos(),p));
}

void Maze::delPost(Position pos){  // delete Post at a Position (works fine because there can never be 2 posts on the same position)
    this->posts.erase(posts.find(pos));
}

mapPost& Maze::getPostMap(){  // get full data structure for posts
    return this->posts;
}

Post& Maze::getPost(Position pos){  // get Post at a Position (works fine because there can never be 2 posts on the same position)
    return this->posts[pos];
}
/**************************************************************************************************************/