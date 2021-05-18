#include "Post.hpp"

Post::Post(char ch, int x, int y){
    if(ch='+') 
        this->electrified=false;
    else 
        this->electrified=true;
    this -> x = x;
    this -> y = y;
}

bool Post::getState() const{
    return this->electrified;
}

void Post::turnOff(){
    this->electrified = false;
}