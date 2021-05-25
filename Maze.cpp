// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"


Maze::Maze(){
    // default constructor
}

void Maze::setMapN(std::string mapName){
    int pos = mapName.find('_');
    int pos1 = mapName.find('.');
    std::string mapN = mapName.substr(pos+1, mapName.length()-pos1);
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

std::string Maze::getMapN(){
    return this->mapN;
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
    this->posts.insert(pair<this->,p>);
}

void Maze::delPost(int i){
    this->posts.erase(posts.begin()+i);
}

Post& Maze::getPost(int index){
    return this->posts[index];
}