// T04_G02

#include "gamestructs.hpp"

#ifndef ENTITY_H
#define ENTITY_H  // avoid compiling errors related to redefinition

class Entity{
public:
    Entity();
    Entity(int x, int y);
	Position getPos() const;  // get the position for an entity
	void setPos(Position newPos);  // set a new position for an entity
	char getSymbol() const;  // get the symbol of an entity for display
	bool isAlive() const;  // returns true if entity is alive, false otherwise
	void kill();  // set bool alive as false (set entity as dead)
protected:
	Position pos;
	bool alive;
	char symbol;
};

#endif