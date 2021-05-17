// T04_G02

class Post{
public:
    Post(char ch);
    bool getState() const;
    void turnOff();

private:
    bool electrified;
};