// T04_G02

#include <iostream>


#ifndef STRUCTS_H
#define STRUCTS_H  // avoid compiling errors related to redefinition


/**************************************************************************************************************/
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
		pos.x = x + move.dx;
		pos.y = y + move.dy;
		return pos;
	}
	
};
/**************************************************************************************************************/


/**************************************************************************************************************/
struct LbEntry{ 
    std::string info;  // player information (name or name + map) (includes extra empty spaces and '-' because it makes formating leaderboards easier)
    int time;  // score (time played)
};
/**************************************************************************************************************/


/**************************************************************************************************************/
struct MapComparator{  // object to be use as a comparator of Positions, allowing us to use them as keys to std::map
    bool operator()(const Position& l, const Position& r) const { return (l.x<r.x || (l.x==r.x && l.y<r.y));}
};
/**************************************************************************************************************/


#endif
