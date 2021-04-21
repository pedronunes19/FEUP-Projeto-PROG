// T04_G02

// header file containing structs for game "characters"

struct Player{
    // coordinates
    int x;
    int y;

    // status
    bool alive;
    
};

struct Robot{
    // coordinates
    int x;
    int y;

    // status
    bool alive;

    // moving order
    int order;
    
};