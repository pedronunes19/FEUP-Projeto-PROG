// T04_G02

class Post{
public:
    Post(char ch, int x, int y);
    char getState() const;
    void turnOff();

private:
    char state;  // 3 states -> '*' for electrified posts, '+' for non electrified posts, 'O' for exits
    int x, y;
};