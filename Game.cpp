// T04_G02

#include "Game.hpp"

using namespace std;

/**************************************************************************************************************/
// EVERYTHING RELATED TO BUILDING THE GAME OBJECT
Game::Game(const string &mapName){
    maze.setMapN(mapName);  // sets the maze with the file name for future use
    ifstream map(mapName);  // open stream to read everything from file
    maze.setDimensions(map);  // store maze dimensions
    setObjectsFromMap(map);
    map.close(); // close stream (map file won't be touched after this)
    timePlayed = -1;  // -1 value signals the game hasn't been played (therefore updateLeaderboards will not work)
}

void Game::setObjectsFromMap(std::ifstream &map){
    std::string currentLine;
    int y = 0;
    while (getline(map,currentLine)){  // reads line by line
        for (int x = 0; x < currentLine.length(); x++) {  // read every character in the line 
            char temp = currentLine[x];
            if (temp == 'H'){  // create the player
                this->player = Player(x,y);
            }
            if (temp == 'R'){  // add a robot
				Position temp = {x, y};
				robots.insert(pair<Position,Robot>(temp,Robot(x,y)));
            }
            if (temp == '*' || temp == '+' || temp == 'O'){  // add any type of post
                Post p(x, y, temp);
                maze.addPost(p);
            }
        }
    y++;
    }
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// PLAY
bool Game::play(){
    cout << "here" << endl;
    bool run = true;  // variable to keep game going
    bool endState;
    auto gameStart = chrono::steady_clock::now();  // starts clock to count gametime
    while(run){
        showDisplay();  // print current state of map
        break;
        /*  NOT WORKING YET
        // check conditions for win/lost, end loop if needed, set boolean for return
        movePlayer();
        moveRobots();
        */
    }
    auto gameEnd = chrono::steady_clock::now();  // time when game is over   
    this -> timePlayed= chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count();  // full time played
    return endState;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// LEADERBOARD
void Game::updateLeaderboards(string mazeLeaderboardFile, bool mazeLeaderboard, bool winnersLeaderboard) const{
    if (timePlayed == -1){  // updating leaderboards should only work for Game objects that have been played (Game::play() called)
        return;
    }
    // read the player's name
    bool emptyName = true;
    string playerName;
    const short int MAXNAMELENGTH = 15;
    while (emptyName){
        cout << "Write your name here (max 15 characters): ";
        getline(cin, playerName);
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (playerName.length() > 0){
            if (playerName.length() > MAXNAMELENGTH){  // cut name at character limit
                playerName = playerName.substr(0, MAXNAMELENGTH);
            }
            else{
                for (int i = playerName.length(); i < MAXNAMELENGTH; i++){  
                    playerName += ' ';  // fill with spaces to fit 15 characters (fits the table better than setw())
                }
            }
            break;
        }
        cout << "You have to choose a name!" << endl;
    }

    // create files with a basic template
    if (!mazeLeaderboard){
        ofstream leaderboard(mazeLeaderboardFile);
        leaderboard << "Player          - Time\n----------------------" << endl;  // write basic leaderboard template
        leaderboard.close();
    }
    if (!winnersLeaderboard){
        ofstream leaderboard("winners.txt");
        leaderboard << "Player          - Map\n---------------------" << endl;  // write basic leaderboard template
        leaderboard.close();
    }

    // write the name and time to the file (map)
    ofstream leaderboard;
    leaderboard.open(mazeLeaderboardFile, ios::app);
    leaderboard << playerName << " - " << timePlayed << endl;
    leaderboard.close();

    organizeLeaderboard(mazeLeaderboardFile);  // ordering maze leaderboard
    
    // still to be decided what to do with the winners one

}
/**************************************************************************************************************/


/**************************************************************************************************************/
// USED BY PLAY
void Game::showDisplay(){
    char *display = new char[maze.getHeight() * maze.getWidth()];  // allocate a array of dimension height*widht (same size as a 2d array to represent the map visually)
    /*
    being x and y the coordinates
    being height and width the dimensions of the map
    the index on the display will be -> x + (y * widht)
    */
    for (int i = 0; i < maze.getHeight() * maze.getWidth(); i++){  // fill display with empty spaces 
        display[i] = ' ';
    }
    for (int i = 0; i < maze.getNumberOfPosts(); i++){  // iterate through posts and place their representation on the display
        Position tempPos = maze.getPost(i).getPos();
        int index = tempPos.x + (tempPos.y*maze.getWidth());  
        display[index] = maze.getPost(i).getChar();
    }

    for(Robot r: robots){  // iterate through robots and place their representation on the display
        Position tempPos = r.getPos();
        int index = tempPos.x + (tempPos.y*maze.getWidth());
        display[index] = r.getSymbol();
    }

    Position tempPos = player.getPos();  // place player's representation on the display
    int index = tempPos.x + (tempPos.y*maze.getWidth());
    display[index] = player.getSymbol();

    for (int i = 0; i < maze.getHeight() * maze.getWidth(); i++){  // iterate through the display, and print every char to the screen
        if (i%maze.getWidth() == 0){  
            cout << "\n";  // print a \n every time it starts printing a new line of the map (y changes)
        }
        cout << display[i];
    }
    cout << endl;
    
    delete[] display;  // delete the space allocated before
}

Movement Game::moveInput(){
    Movement move;  // the movement that will be corresponding to the user's input
    bool validMove; 
    const string VALIDMOVES = "qweasdzxc";  // string containing every char correponding to a valid move
    char moveOption;  // player input
    do{
        validMove = true;
        cout << "Move -> ";
        cin >> moveOption;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // remove the rest of the line from input buffer
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (cin.fail()){  // staying as a safety measure
            cin.clear();
            cout << "Invalid input" << endl;
            validMove = false;
            continue;
        }
        if (VALIDMOVES.find(moveOption) == string::npos){  // invalid input if moveOption is not in VALIDMOVES
            cout << "Invalid input" << endl;
            validMove = false;
            continue;
        }
        
    }while(!validMove);

    moveOption = tolower(moveOption);  // avoid case sensitivity
    // define movement on x axis
    if (moveOption == 'e' || moveOption == 'd' || moveOption == 'c') 
        move.dx = 1;        
    else if (moveOption == 'q' || moveOption == 'a' || moveOption == 'z') 
        move.dx = -1;
    else 
        move.dx = 0;

    // define movement on y axis
    if (moveOption == 'z' || moveOption == 'x' || moveOption == 'c') 
        move.dy = 1;       
    else if (moveOption == 'q' || moveOption == 'w' || moveOption == 'e') 
        move.dy = -1;
    else 
        move.dy = 0;

    return move;   
}

void Game::movePlayer()
{
    bool moved = false;
    Movement move = moveInput();
    for(Robot& robot: robots){
        while(!valid_move(player,robot,move)){
            Movement move = moveInput();
        }
    }
}

bool Game::valid_move(Robot& robot, int postIndex, Movement mov)            //Returns true if first arg can move
{
    Post& post = maze.getPost(postIndex);       //Get post reference
    Position newPos = player.getPos() + mov;

    if(newPos == robot.getPos()){       
        if(post.isElectrified()){
            robot.kill();
            post.turnOff();
            return false;
        }
        else{
            robot.kill();
            maze.delPost(postIndex);
        }
    }
    return true;
}

bool Game::valid_move(Player& player, Robot& robot, Movement mov)           //Returns true if first arg can move
{
    Position newPos = player.getPos() + mov;
    if(newPos == robot.getPos()){
        if(robot.isAlive()){
            player.kill();
            return true;
        }
        return false;
    }
    return true;
}

bool Game::valid_move(Robot& robot0, Robot& robot1, Movement mov)           //Returns true if first arg can move
{
    Position newPos = robot0.getPos() + mov;
    if(newPos == robot1.getPos()){
        robot0.kill();
        robot1.kill();
    }
    return true;
}

bool Game::valid_move(Player& player, Post& post, Movement mov)             //Returns true if first arg can move
{
    Position newPos = player.getPos() + mov;
    if(newPos == post.getPos()){
        if(post.isElectrified()){
            player.kill();
            return true;
        }
        else if(post.isExit()){
            playerExits();
            return true;
        }
        return false;
    }
    return true;
}


void Game::playerExits(){
    this->playerExited = true;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// USED BY UPDATELEADERBOARDS
void Game::organizeLeaderboard(string lbPath) const{
    vector <LbEntry> entries;  // vector to store leaderboard entries
    readEntries(lbPath, entries);  // read all entries
    ofstream lbFile(lbPath);
    lbFile << "Player          - Time" << endl << "----------------------" << endl;  // write the first 2 lines back to file

    sort(entries.begin(), entries.end(), [](const LbEntry& lb0, const LbEntry& lb1) -> bool {return lb0.time < lb1.time;});  // sort entries vector by time
    for(int i = 0; i < entries.size(); i++) {
        lbFile << entries[i].name << entries[i].time << endl;
    }
    lbFile.close();  // close file after writing ordered leaderboard to file
}

void Game::readEntries(string lbPath, vector <LbEntry> &entries) const{
    ifstream lbFile(lbPath);   // open leaderboard file for reading
    string currentLine;
    const int NAMELENGTH = 18;
    
    // skip first 2 lines
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while(getline(lbFile, currentLine)){
        LbEntry currentEntry;

        // store entries
        currentEntry.name = currentLine.substr(0, NAMELENGTH);
        currentEntry.time = stoi(currentLine.substr(NAMELENGTH, string::npos - 1));
        entries.push_back(currentEntry);
    }
    lbFile.close();  // close file after reading
}