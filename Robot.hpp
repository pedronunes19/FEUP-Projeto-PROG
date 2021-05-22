#include "gamestructs.hpp"

class Robot {
public:
	Robot(int x, int y);
	Robot(Position pos);
	int getID() const;
	char getSymbol() const;
	Position getPos() const;
	bool isAlive() const;
	void move(Movement move);
	void kill();

private:
	static int robotCounter;
	int id;
	Position pos;
	bool alive;
	char symbol;
}

