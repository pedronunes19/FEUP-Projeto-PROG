// T04_G02

#include "Player.hpp"


/**************************************************************************************************************/
// CONSTRUCTORS
Player::Player(){
	// default constructor
}

Player::Player(int x, int y) : Entity::Entity(x, y)
{
	symbol = 'H';
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// GET INFO
bool Player::hasExited() const{
	return exited;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// ACTIONS
void Player::exit(){
	exited = true;
}
/**************************************************************************************************************/