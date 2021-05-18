// T04_G02
#include <vector>
using namespace std;

class Robot
{
public:
    Robot();
    void setPos(const vector<int> &new_pos);
    vector<int> getPos() const;
    void kill();

private:
    vector<int> pos{2};
    bool alive;
};