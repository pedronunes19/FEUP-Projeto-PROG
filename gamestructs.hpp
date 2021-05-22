struct Movement {
	int dx, dy;
};

struct Position {
	int x, y;
	bool operator==(const Position& pos)
	{
		return (x==pos.x && y==pos.y);
	}
};

