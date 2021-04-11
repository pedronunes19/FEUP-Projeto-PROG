// header file containing structs for game "characters"

struct player{
    // coordinates
    int x;
    int y;

    // status
    bool alive;

    // presentation
    char sprites[2] = {'h', 'H'};
};

struct robot{
    // coordinates
    int x;
    int y;

    // status
    bool alive;

    // moving order
    int order;

    // presentation
    char sprites[2] = {'r', 'R'};
};