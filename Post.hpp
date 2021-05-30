// T04_G02

#ifndef POST_H
#define POST_H  // avoid compiling errors related to redefinition

#include "gamestructs.hpp"

class Post{
    public:
        Post();
        Post(int x, int y, char ch );  // constructor
	    Position getPos() const;  //  returns the position
        bool isElectrified() const;  // returns true if the post in question is an electrified one (checks the symbol)
        void turnOff();  // set a post to non electrified
        bool isExit() const;  // returns true if the post in question is an exit (checks the symbol)
        char getSymbol() const;  // get the symbol for display

    private:
        char symbol;  // 3 symbols -> '*' for electrified posts, '+' for non electrified posts, 'O' for exits
	    Position pos;  // position
};

#endif