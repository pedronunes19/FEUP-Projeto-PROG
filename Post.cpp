#include "Post.hpp"

Post::Post(int x, int y, char ch)
{
	this->pos.x = x;
	this->pos.y = y;

	this->electrified = ch;
}

Position Post::getPos() const
{
	return this->pos;
}

bool Post::isElectrified() const
{
	if ( this->electrified == '*' ) return true;
	return false;
}

void Post::turnOff()
{
	this->electrified = '+';
}