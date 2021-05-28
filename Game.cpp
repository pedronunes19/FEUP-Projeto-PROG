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
            else if (temp == 'R'){  // add a robot
                Position tempPos = {x, y};
                robots.push_back(Robot(x,y));
				robotsMap.insert(pair<Position,Robot*>(tempPos,&robots[robots.size()-1]));  // TO CHANGE!!!!!!!!! doing it here lead to store outdated pointers
            }
            else if (temp == '*' || temp == '+' || temp == 'O'){  // add any type of post
                Post p(x, y, temp);
                maze.addPost(p);
            }
        }
    y++;
    }
    // DO ROBOTSMAP HERE INSTEAD
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// PLAY
bool Game::play(){
    bool run = true;  // variable to keep game going
    auto gameStart = chrono::steady_clock::now();  // starts clock to count gametime
    while(run){
        showDisplay();  // print current state of map
        if (gameOver()){
            break;
        }
        movePlayer();
        moveRobots();
    }
    auto gameEnd = chrono::steady_clock::now();  // time when game is over   
    this -> timePlayed= chrono::duration_cast<chrono::seconds>(gameEnd - gameStart).count();  // full time played
    return gameResult;
}
/**************************************************************************************************************/


/**************************************************************************************************************/
// LEADERBOARD
void Game::updateLeaderboards(string mazeLeaderboardFile, bool mazeLeaderboard, bool winnersLeaderboard){
    if (timePlayed == -1){  // updating leaderboards should only work for Game objects that have been played (Game::play() called)
        return;
    }
    // read the player's name
    string playerName;
    const short int MAXNAMELENGTH = 15;
    do{
        cout << "Write your name here (max 15 characters): ";
        getline(cin, playerName);
        if (cin.eof()){  // end with CTRL-Z/CTRL-D
            cout << "Program terminated with CTRL-Z or CTRL-D";
            exit(0);
        }
        if (playerName.length() > MAXNAMELENGTH){  // cut name at character limit
                playerName = playerName.substr(0, MAXNAMELENGTH);
            }
        cout << "You have to choose a name!" << endl;
    }while (playerName.empty());

    // may be needed (if not then loop doesn't start)
    for (int i = playerName.length(); i < MAXNAMELENGTH; i++){  
        playerName += ' ';  // fill with spaces to fit 15 characters (fits the table better than setw())
    }

    // create files with a basic template
    if (!mazeLeaderboard){
        ofstream leaderboard(mazeLeaderboardFile);
        leaderboard << "Player          - Time\n----------------------" << endl;  // write basic leaderboard template
        leaderboard.close();
    }
    if (!winnersLeaderboard){
        ofstream leaderboard("winners.txt");
        leaderboard << "Player          - Map - Time\n----------------------------" << endl;  // write basic leaderboard template
        leaderboard.close();
    }

    // write the name and time to the file (map)
    ofstream leaderboard0;
    leaderboard0.open(mazeLeaderboardFile, ios::app);
    leaderboard0 << playerName << " - " << timePlayed << endl;
    leaderboard0.close();

    organizeLeaderboard(mazeLeaderboardFile);  // ordering maze leaderboard

    ofstream leaderboard1;
    leaderboard1.open("winners.txt", ios::app);
    leaderboard1 << playerName << " - " << setw(3) << maze.getMapN() << " - " << timePlayed << endl;
    leaderboard1.close();

    organizeLeaderboard("winners.txt");  // ordering maze leaderboard
    

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
    for (auto i = maze.getPostMap().begin(); i != maze.getPostMap().end(); i++){  // iterate through posts and place their representation on the display
        Position tempPos = i->first;
        int index = tempPos.x + (tempPos.y*maze.getWidth());  
        display[index] = i->second.getChar();
    }

    for(auto const& r: robots){  // iterate through robots and place their representation on the display
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
    bool const LOOP = true;
    Position newPos;
    Movement move;

    //validCollision() will check validity of the collision and perform corresponding actions if valid
    /*while(true) loop and exception handling are used to avoid creating 2 different variables for the possibly found robot/post at newPos (like the iterator returned by map.find()),
    verifying both of their contents to check if a robot/post was found and calling validCollision() with either robot or post as parameter depending on which one was found. */
    while(LOOP){    //infinite loop, will break when a valid move is found
        move = moveInput();
        newPos = player.getPos()+move;
        try{
            Robot* collideEntity = robotsMap.at(newPos);       //if robot is found at newPos then check collide, else out_of_range and check if there is a post
            if(!validCollision(player,*collideEntity,newPos)) continue;    //restart cicle if collision is not valid
            break;  //break if robot was found and collision is valid
        }
        catch(out_of_range){
            try{
                Post& collideEntity = maze.getPostMap().at(newPos);     //if post is found at newPos then check collide, else out_of_range and break since player moved to empty space
                if(!validCollision(player,collideEntity,newPos)) continue;    //restart cicle if collision is not valid
                break;  //break if post was found and collision is valid
            }
            catch(out_of_range){
                break;      //no collisions
            }
        }
    }
    player.move(move);
}

void Game::moveRobots()
{   
    Position playerPos = player.getPos();
    for (Robot& robot: robots){
        if (!player.isAlive()) 
            return;  // end robot movement if player is dead
        if (!robot.isAlive()) 
            continue;  // skip if robot is dead

        Position robotPos = robot.getPos();
        Movement move;

        if(robotPos.x < playerPos.x)                     // define movement on x axis
            move.dx = 1;        
        else if (robotPos.x > playerPos.x) 
            move.dx = -1;
        else 
            move.dx = 0;

        if(robotPos.y < playerPos.y)                     // define movement on y axis
            move.dy = 1;        
        else if (robotPos.y > playerPos.y) 
            move.dy = -1;
        else 
            move.dy = 0;

        Position newPos = robotPos + move;
        
        try{
            Post& collideEntity = maze.getPostMap().at(newPos);
            if(!validCollision(robot,collideEntity,newPos)) continue;
        }
        catch(out_of_range){
            try{
                Robot* collideEntity = robotsMap.at(newPos);
                robot.kill();
                collideEntity->kill();
                robotsMap.erase(robotsMap.find(newPos));

            }
            catch(out_of_range){
                if(newPos == playerPos) 
                    player.kill();
            }
        }
        robot.move(move);
        robotsMap.erase(robotsMap.find(robotPos));   // erase element with old pos
        robotsMap[newPos] = &robot;  // create new element with new pos as key and pointer to current robot
    }
}

bool Game::validCollision(Robot& robot, Post& post, Position newPos)            //Returns true if first arg can move to newPos
{
    if(newPos == post.getPos()){       
        if(post.isElectrified()){
            robot.kill();
            post.turnOff();
            return false;
        }
        else{
            robot.kill();
            maze.delPost(newPos);
        }
    }
    return true;
}

bool Game::validCollision(Player& player, Robot& robot, Position newPos)           //Returns true if first arg can move to newPos
{
    if(newPos == robot.getPos()){
        if(robot.isAlive()){
            player.kill();
            return true;
        }
        return false;
    }
    return true;
}

bool Game::validCollision(Player& player, Post& post, Position newPos)             //Returns true if first arg can move to newPos
{
    if(newPos == post.getPos()){
        if(post.isElectrified()){
            player.kill();
            return true;
        }
        else if(post.isExit()){
            player.exit();
            return true;
        }
        return false;
    }
    return true;
}

bool Game::gameOver(){
    if(!player.isAlive()){  // end if player is dead, otherwise continue verification
        gameResult = false;
        return true;
    }
    if(player.hasExited()){  // end if player has found an exit, otherwise continue verification
        gameResult = true;
        return true;
    }
    return false;
}

/**************************************************************************************************************/


/**************************************************************************************************************/
// USED BY UPDATELEADERBOARDS
void Game::organizeLeaderboard(string lbPath) const{
    vector <LbEntry> entries;  // vector to store leaderboard entries
    readEntries(lbPath, entries);  // read all entries
    ofstream lbFile(lbPath);
    if (lbPath == "winners.txt"){
        lbFile << "Player          - Map - Time\n----------------------------" << endl;  // write the first 2 lines back to file
    }
    else
        lbFile << "Player          - Time\n----------------------" << endl;  // write the first 2 lines back to file

    sort(entries.begin(), entries.end(), [](const LbEntry& lb0, const LbEntry& lb1) -> bool {return lb0.time < lb1.time;});  // sort entries vector by time
    for(int i = 0; i < entries.size(); i++) {
        lbFile << entries[i].info << entries[i].time << endl;
    }
    lbFile.close();  // close file after writing ordered leaderboard to file
    entries.clear();  // delete everything from entries vector (would happen anyways at the declaration at the start of organizeLeaderboard when the function is called, it's just a little add-on)
}

void Game::readEntries(string lbPath, vector <LbEntry> &entries) const{
    ifstream lbFile(lbPath);   // open leaderboard file for reading
    string currentLine;
    const short int OFFSET = 6;  // offset to add in the general leaderboard, 3 chars for map and 3 chars for " - "
    const short int NAMELENGTH = 18;  // max size of the name plus 3 characters (corresponding to " - ")
    
    // skip first 2 lines
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    lbFile.ignore(numeric_limits<streamsize>::max(), '\n');
    
    while(getline(lbFile, currentLine)){
        LbEntry currentEntry;

        // store entries
        if (lbPath == "winners.txt"){
            currentEntry.info = currentLine.substr(0, NAMELENGTH + OFFSET);
            currentEntry.time = stoi(currentLine.substr(NAMELENGTH + OFFSET, string::npos - 1));
        }
        else{
            currentEntry.info = currentLine.substr(0, NAMELENGTH);
            currentEntry.time = stoi(currentLine.substr(NAMELENGTH, string::npos - 1));
        }
        entries.push_back(currentEntry);
    }
    lbFile.close();  // close file after reading
}