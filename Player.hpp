// T04_G02

#ifndef PLAYER_H
#define PLAYER_H  // avoid compiling errors related to redefinition

#include "gamestructs.hpp"

class Player {
public:
    Player();
	Player(int x, int y);
	Position getPos() const;
	char getSymbol() const;
	bool isAlive() const;
	bool hasExited() const;
	void kill();
	void move(Movement delta);
	void exit();  // signals that the player has found an exit
private:
	Position pos;
	bool alive, exited;
	char symbol;
};

#endif