// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"


Maze::Maze(){
    // default constructor
}

void Maze::setMapName(std::string mapName){
    this -> mapName = mapName;
}


void Maze::setDimensions(std::ifstream &map){  // uses the first line of the file to read dimensions + removes that line from filestream
    std::string firstLine;
    getline(map, firstLine);
    std::stringstream ss;
    ss << firstLine;
    char aux;
    ss >> height >> aux >> width;
}

std::string Maze::getMapName(){
    return this->mapName;
}


int Maze::getHeight() const{
    return this->height;
}

int Maze::getWidth() const{
    return this->width;
}

int Maze::getNumberOfPosts() const{
    return this->posts.size();
}

void Maze::addPost(Post p){
    posts.push_back(p);
}

void Maze::delPost(int i){
    this->posts.erase(posts.begin()+i);
}

Post& Maze::getPost(int index){
    return this->posts[index];
}