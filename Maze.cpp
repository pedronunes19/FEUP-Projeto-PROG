// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"
#include "Post.hpp"

Maze::Maze(){

}

void Maze::setFile(std::string name){
    this -> mapFile = name;
}

void Maze::setDimensions(std::ifstream &map){
    std::string firstLine;
    getline(map, firstLine);
    std::stringstream ss;
    ss << firstLine;
    char aux;
    ss >> height >> aux >> width;
}

std::string Maze::getFileName(){
    return mapFile;
}