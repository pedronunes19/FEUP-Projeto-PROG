// T04_G02

#ifndef POST_H
#define POST_H  // avoid compiling errors related to redefinition

#include "gamestructs.hpp"

class Post{
    public:
        Post();
        Post(int x, int y, char ch );  // constructor
	    Position getPos() const;  //returns the position
        bool isElectrified() const;
        void turnOff();
        bool isExit() const;
        char getSymbol() const;

    private:
        char symbol;  // 3 symbols -> '*' for electrified posts, '+' for non electrified posts, 'O' for exits
	    Position pos;  // position
};

#endif