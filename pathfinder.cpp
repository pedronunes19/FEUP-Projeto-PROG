#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void getMapVector( ifstream& mapFile, vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <int>& PlayerPosition );
void getMapSize( ifstream& mapFile, int& height, int& width );
void printMap(vector <vector <char>>& map);
void move( vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <int>& PlayerPosition);

int main() {
	ifstream mapFile( "MAZE_02.txt" );
	vector <vector <char>> mapVector;
	vector <vector <int>> RobotPositions;
    vector <int> PlayerPosition;
	int height, width;

    getMapSize(mapFile, height, width);
    getMapVector(mapFile, mapVector, RobotPositions, PlayerPosition);
    printMap(mapVector);
    move(mapVector, RobotPositions, PlayerPosition);
    printMap(mapVector);
}

void getMapSize( ifstream& mapFile, int& height, int& width ) {  // function to get map size (height, width) by reading the numbers from the first line of the file
	string firstLine;
	getline( mapFile, firstLine );
	const int pos = firstLine.find( " " );
	height = stoi( firstLine.substr( 0, pos ) );
	width = stoi( firstLine.substr( pos + 3, string::npos ) );
}

void getMapVector( ifstream& mapFile, vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <int>& PlayerPosition ) {  // function to read map from file to vector
	int i = 0;
	int robotsfound;
	string currentLine = "";

	while ( getline( mapFile, currentLine ) ) {  // reads line by line
		vector <char> temp;
		vector <int> tempPos( 2 );
		char ch;
		for ( int j = 0; j < currentLine.length(); j++ ) {  // push every character in the line to the vector
			ch = currentLine[j];
			temp.push_back( ch );
			if ( ch == 'R' ) { 
				tempPos.at(0) = i;
				tempPos.at(1) = j;
				RobotPositions.push_back( tempPos );
			}
			else if ( ch == 'H' ) { 
				PlayerPosition.at( 0 ) = i;
				PlayerPosition.at( 1 ) = j;
			}

		}
		map.push_back( temp );
		i++;
	}

}

void printMap(vector <vector <char>>& map){  //  function to print the map from map vector
    for (int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[i].size(); j++){
            cout << map.at(i).at(j);
        }
        cout << endl;
    }
}

void move( vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <int>& PlayerPosition) {
    char temp;
    vector <int> direction(2);
    for(int i = 0; i < RobotPositions.size(); i++){
        vector <int> robot = RobotPositions[i];
    
        if(robot[0] < PlayerPosition[0]) direction[0] = 1;
        else if (robot[0] > PlayerPosition[0]) direction[0] = -1;
        else direction[0] = 0;

        if(robot[1] < PlayerPosition[1]) direction[1] = 1;
        else if (robot[1] > PlayerPosition[1]) direction[1] = -1;
        else direction[1] = 0;    

        temp = map[robot[0]+direction[0]][robot[1]+direction[1]];
        map[robot[0]+direction[0]][robot[1]+direction[1]] = map[robot[0]][robot[1]];
        map[robot[0]][robot[1]] = temp;
    }
}
