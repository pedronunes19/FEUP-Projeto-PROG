#pragma once

struct Movement {
	int dx, dy;
};

struct Position {
	int x, y;
	bool operator==(const Position& pos)
	{
		return (x==pos.x && y==pos.y);
	}

	Position operator+(const Movement& move)
	{
		Position pos;
		pos.x += move.dx;
		pos.y += move.dy;
		return pos;
	}
};

