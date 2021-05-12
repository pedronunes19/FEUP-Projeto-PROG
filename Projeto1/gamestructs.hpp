// T04_G02
// header file containing structs for game "characters" + leaderboard entries
// Player and Robot are separated to improve understanding of the code

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
    
};

struct LbEntry{ 

    // player name
    std::string name;

    // score (time played)
    int time;

};
