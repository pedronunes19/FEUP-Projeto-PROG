// T04_G02

#ifndef ROBOT_H
#define ROBOT_H  // avoid compiling errors related to redefinition

#include "Entity.hpp"
#include "gamestructs.hpp"

class Robot: public Entity{
public:
	Robot(int x, int y);
	int getID() const;  // returns id value

private:
	static int robotCounter;
	int id;
};

#endif