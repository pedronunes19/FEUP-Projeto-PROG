// T04_G02

#ifndef POST_H
#define POST_H  // avoid compiling errors related to redefinition

#include "gamestructs.hpp"

class Post{
public:
    Post(int x, int y, char ch );
	Position getPos() const;
    bool isElectrified() const;
    void turnOff();
    bool isExit() const;
    char getChar() const;

private:
    char state;  // 3 states -> '*' for electrified posts, '+' for non electrified posts, 'O' for exits
	Position pos;
};

#endif