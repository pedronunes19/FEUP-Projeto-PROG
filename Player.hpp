#include "gamestructs.hpp"

class Player {
public:
    Player();
	Player(int x, int y);
	Position getPos() const;
	char getSymbol() const;
	bool isAlive() const;
	void kill();
	bool move(Movement delta);
private:
	Position pos;
	bool alive;
	char symbol;
};