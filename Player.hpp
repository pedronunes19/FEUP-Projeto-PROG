// T04_G02

#include <vector>


class Player{
public:
    Player();
    void setPos(const std::vector<int> &new_pos);
    std::vector<int> getPos() const;
private:
    std::vector<int> pos{2};
};