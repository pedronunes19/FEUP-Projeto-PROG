// T04_G02

#ifndef PLAYER_H
#define PLAYER_H  // avoid compiling errors related to redefinition

#include "Entity.hpp"
#include "gamestructs.hpp"

class Player: public Entity {
public:
    Player();
	Player(int x, int y);
	bool hasExited() const;  // signals that the player has found an exit
	void exit();  // set exited to true (the player has now found an exit to the maze)
private:
	bool exited;
};

#endif