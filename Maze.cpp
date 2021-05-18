// T04_G02

#include <iostream>
#include <vector>
#include "Maze.hpp"
#include "Post.hpp"

Maze::Maze(){

}

Maze::Maze(std::string mapName){
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

void Maze::setMapVector(std::ifstream &map){
    std::string currentLine;
    while (getline(map,currentLine)){  // reads line by line
        std::vector <char> temp;
        for (int j = 0; j < currentLine.length(); j++) {  // read every character in the line 
            char aux = currentLine[j];
            temp.push_back(aux);  // add the caracter to the vector that contains the line
        }
        mapVector.push_back(temp);  // push the vector created with the line to map vector
        
    }
}

int Maze::getHeight() const{
    return height;
}

int Maze::getWidth() const{
    return width;
}

char Maze::getChar(int x, int y){
    return mapVector.at(y).at(x);
}

void Maze::addPost(Post p){
    posts.push_back(p);
}