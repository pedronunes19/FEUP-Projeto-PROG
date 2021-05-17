// T04_G02
#include "Robot.hpp"

Robot::Robot(){
    this->alive=true;
}

void Robot::setPos(const vector<int> &new_pos){
    this->pos[0] = new_pos[0];
    this->pos[1] = new_pos[1];
}

vector<int> Robot::getPos() const{
    return this->pos;
}

void Robot::kill(){
    this ->alive = false;
}