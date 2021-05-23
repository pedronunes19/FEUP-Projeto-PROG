#include "gamestructs.hpp"

class Robot {
public:
	Robot(int x, int y);
	int getID() const;
	char getSymbol() const;
	Position getPos() const;
	bool isAlive() const;
	void kill();
	void move(Movement delta);

private:
	static int robotCounter;
	int id;
	Position pos;
	bool alive;
	char symbol;
};

