#include "gamestructs.hpp"

class Player {
public:
	Player(int x, int y);
	Player(Position pos);
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