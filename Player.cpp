// T04_G02

#include "Player.hpp"

Player::Player(){
    this -> alive = true;
}

void Player::setPos(const std::vector<int> &new_pos){
    this->pos[0] = new_pos[0];
    this->pos[1] = new_pos[1];
}

std::vector<int> Player::getPos() const{
    return this->pos;
}