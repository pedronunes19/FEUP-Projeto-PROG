#include "Post.hpp"

Post::Post(int x, int y, char ch)
{
	this->pos.x = x;
	this->pos.y = y;

	this->state = ch;
}

Position Post::getPos() const
{
	return this->pos;
}

bool Post::isElectrified() const
{
	return ( this->state == '*' );
}

void Post::turnOff()
{
	this->state = '+';
}

bool Post::isExit() const
{
	return ( this->state == 'O' );
}

char Post::getChar() const{
	return this->state;
}