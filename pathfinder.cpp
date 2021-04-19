#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void getMapVector( ifstream& mapFile, vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <vector <int>>& PlayerPositions );
void getMapSize( ifstream& mapFile, int& height, int& width );


int main() {
	ifstream mapFile( "MAZE_02.txt" );
	vector <vector <char>> mapVector;
	vector <vector <int>> RobotPositions, PlayerPositions;
	int height, width;


}

void getMapSize( ifstream& mapFile, int& height, int& width ) {  // function to get map size (height, width) by reading the numbers from the first line of the file
	string firstLine;
	getline( mapFile, firstLine );
	const int pos = firstLine.find( " " );
	height = stoi( firstLine.substr( 0, pos ) );
	width = stoi( firstLine.substr( pos + 3, string::npos ) );
}

void getMapVector( ifstream& mapFile, vector <vector <char>>& map, vector <vector <int>>& RobotPositions, vector <vector <int>>& PlayerPositions ) {  // function to read map from file to vector
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
				tempPos.at( 0 ) = i;
				tempPos.at( 1 ) = j;
				PlayerPositions.push_back( tempPos );
			}

		}
		map.push_back( temp );
		i++;
	}

}

void path( vector <vector <char>>& map ) {


}
