// T04_G02

class Post{
public:
    Post(char ch, int x, int y);
    char getState() const;
    void turnOff();

private:
    char state;
    int x, y;
};