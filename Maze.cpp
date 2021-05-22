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


void Maze::setDimensions(std::ifstream &map){
    std::string firstLine;
    getline(map, firstLine);
    std::stringstream ss;
    ss << firstLine;
    char aux;
    ss >> height >> aux >> width;
}

std::string Maze::getMapName(){
    return mapName;
}


int Maze::getHeight() const{
    return height;
}

int Maze::getWidth() const{
    return width;
}

void Maze::addPost(Post p){
    posts.push_back(p);
}