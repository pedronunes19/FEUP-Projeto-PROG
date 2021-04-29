// T04_G02
// header file containing structs for game "characters" + leaderboard entries

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

    // moving order id (mostly a formality)
    int id;
    
};

struct LbEntry{ 

    // player name
    std::string name;

    // score (time played)
    int time;

};
