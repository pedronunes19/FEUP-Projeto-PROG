#include "Robot.hpp"

int Robot::robotCounter = 0;

Robot::Robot(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->symbol = 'R';
	this->alive = true;
	this->id = ++robotCounter;
}

Robot::Robot(Position pos)
{
	this->pos = pos;
	this->symbol = 'R';
	this->alive = true;
	this->id = ++robotCounter;
}

int Robot::getID() const
{
	return this->id;
}

Position Robot::getPos() const
{
	return this->pos;
}

char Robot::getSymbol() const
{
	return this->symbol;
}

bool Robot::isAlive() const
{
	return this->alive;
}

void Robot::kill()
{
	this->alive = false;
	this->symbol = 'r';
}