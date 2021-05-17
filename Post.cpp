#include "Post.hpp"

Post::Post(char ch){
    if(ch='+') this->electrified=false;
    else this->electrified=true;
}

bool Post::getState() const{
    return this->electrified;
}

void Post::turnOff(){
    this->electrified = false;
}