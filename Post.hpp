// T04_G02

class Post{
public:
    Post(char ch, int x, int y);
    bool getState() const;
    void turnOff();

private:
    bool electrified;
    int x, y;
};