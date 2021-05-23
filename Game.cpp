// T04_G02

#include "Game.hpp"

using namespace std;

Game::Game(const string &mapName){
    maze.setMapName(mapName);  // sets the maze with the file name for future use
    ifstream map(mapName);  // open stream to read everything from file
    maze.setDimensions(map);  // store maze dimensions
    setObjectsFromMap(map);
    map.close(); // close stream (map file won't be touched after this)
}

void Game::setObjectsFromMap(std::ifstream &map){
    std::string currentLine;
    int y = 0;
    while (getline(map,currentLine)){  // reads line by line
        for (int x = 0; x < currentLine.length(); x++) {  // read every character in the line 
            char temp = currentLine[x];
            if (temp == 'H'){
                this->player = Player(x,y);
            }
            if (temp == 'R'){
                robots.push_back(Robot(x,y));
            }
            if (temp == '*' || temp == '+' || temp == 'O'){
                Post p(x, y, temp);
                maze.addPost(p);
            }
        }
    y++;
    }
}

bool Game::play(){
    bool run = true;  // variable to keep game going
    bool endState;
    auto gameStart = chrono::steady_clock::now();  // starts clock to count gametime
    while(run){
        /*  NOT WORKING YET
        showDisplay();  // print current state of map
        // check conditions for win/lost, end loop if needed, set boolean for return
        movePlayer();
        moveRobots();
        */
    }
    auto gameEnd = chrono::steady_clock::now();  // time when game is over   
    this -> timePlayed= chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count();  // full time played
    return endState;
}

void Game::movePlayer()
{
    Movement move;
    bool validMove;
    const string VALIDMOVES = "qweasdzxc";  // string containing every char correponding to a valid move
    char moveOption;
    // verify movement validity for player
    do{
        validMove = true;
        cout << "Move -> ";
        cin >> moveOption;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(99);
        }
        if (cin.fail()){  // staying as a safety measure
            cin.clear();
            cout << "Invalid move, choose another direction" << endl;
            validMove = false;
            continue;
        }
        if (VALIDMOVES.find(moveOption) == string::npos){
            cout << "Invalid move, choose another direction" << endl;
            validMove = false;
            continue;
        }
        moveOption = tolower(moveOption);  // avoid case sensitivity
        if (moveOption == 'e' || moveOption == 'd' || moveOption == 'c') move.dx = 1;        // define movement on x axis
        else if (moveOption == 'q' || moveOption == 'a' || moveOption == 'z') move.dx = -1;
        else move.dx = 0;

        if (moveOption == 'z' || moveOption == 'x' || moveOption == 'c') move.dy = 1;        // define movement on y axis
        else if (moveOption == 'q' || moveOption == 'w' || moveOption == 'e') move.dy = -1;
        else move.dy = 0;

        Position temp = this->player.getPos() + move;
        for (Robot r: robots){
            if (r.getPos() == temp){
                if (r.isAlive()){
                    this->player.kill(); // kill player
                    this->player.move(move);
                    return;
                }
                if (!r.isAlive()){
                    cout << "Invalid move, choose another direction" << endl;
                    validMove = false;
                    break;
                }
            }
        }
        if (validMove == false){  // skip Post verification if the move is already invalid after checking robots
            continue; 
        }
        for (int i = 0; i < maze.getNumberOfPosts(); i++){
            if (maze.getPost(i).getPos() == temp){
                if (maze.getPost(i).isExit()){
                    
                    this->player.move(move);
                    return;
                }
                if (maze.getPost(i).isElectrified()){
                    this->player.kill(); // kill player
                    this->player.move(move);
                    return;
                }
                if (!maze.getPost(i).isElectrified()){
                    cout << "Invalid move, choose another direction" << endl;
                    validMove = false;
                    break;
                }
            }
        }
    }while(!validMove);

    this->player.move(move);
}

bool Game::collide(Robot& robot, Post& post)
{
    return (robot.getPos() == post.getPos());
}

bool Game::collide(Player& player, Robot& robot)
{
    if(player.getPos() == robot.getPos()){
        if(robot.isAlive()){
            player.kill();
            return true;
        }
        return false;
    }
    return true;
}

bool Game::collide(Robot& robot0, Robot& robot1)
{
    return (robot0.getPos()==robot1.getPos());
}

bool Game::collide(Player& player, Post& post)
{
    if(player.getPos() == post.getPos()){
        if(post.isElectrified()){
            player.kill();
            return true;
        }
        return false;
    }
    return true;
}
