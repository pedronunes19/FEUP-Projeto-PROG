// T04_G02

#include "Player.hpp"

Player::Player(){
	// default constructor
}

Player::Player(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->alive = true;
	this->symbol = 'H';
}


/**************************************************************************************************************/
// GET INFO
Position Player::getPos() const
{
	return this->pos;
}

char Player::getSymbol() const
{
	return this->symbol;
}

bool Player::isAlive() const
{
	return this->alive;
}

bool Player::hasExited() const{
	return this->exited;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// ACTIONS
void Player::kill()
{
	this->alive = false;
	this->symbol = 'h';
}

void Player::move(Movement delta)
{
	this->pos = this->pos + delta;
}

void Player::exit(){
	this->exited = true;
}
/**************************************************************************************************************/