// T04_G02

#ifndef STRUCTS_H
#define STRUCTS_H  // avoid compiling errors related to redefinition

struct Movement {  // represents a movement (a direction)
	int dx, dy;
};

struct Position {  // represents a position (coordinates)
	int x, y;
	bool operator==(const Position& pos)  // overloaded operator "==" to compare position of diferent objects
	{
		return (x==pos.x && y==pos.y);
	}

	Position operator+(const Movement &move) // overloaded operator "+" to add a movement to the position (getting a new position that reflects that movement)
	{
		Position pos;
		pos.x += move.dx;
		pos.y += move.dy;
		return pos;
	}
};

#endif