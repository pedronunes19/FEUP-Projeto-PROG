// T04_G02

#include "gamestructs.hpp"

#ifndef ENTITY_H
#define ENTITY_H  // avoid compiling errors related to redefinition

class Entity{
public:
    Entity();
    Entity(int x, int y);
	Position getPos() const;
	void setPos(Position newPos);
	char getSymbol() const;
	bool isAlive() const;
	void kill();
protected:
	Position pos;
	bool alive;
	char symbol;
};

#endif