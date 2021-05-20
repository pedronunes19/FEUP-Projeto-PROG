#include "Post.hpp"

Post::Post(char ch, int x, int y){
    this -> state = ch;
    this -> x = x;
    this -> y = y;
}

char Post::getState() const{
    return this->state;
}

void Post::turnOff(){
    this -> state = '+';
}