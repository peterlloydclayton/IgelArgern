
/*
a. File Name: Board.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: header file for the Board
*/

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <typeinfo>
#include "Player.h"
#include "RegularSquare.h"
#include "Square.h"
#include "TrapSquare.h"
#include "BlackholeTrap.h"
#include "DeepTrap.h"
#include "NormalTrap.h"
#include "ShallowTrap.h"
#include "WormholeTrap.h"

using namespace std;

class Board {
private:
	vector<vector<Square*>> board; // the primary container for the game

	int rows, columns, hedgeHogsPerPlayer, numberOfPlayers, numberOfTraps;
	int cellWidth = 14;
	string label;
	list<Player> players;

	// Display Functionality
	void getMiddleSquares(int boardRows, int boardColumns);  
	
	// Trap functionality
	unordered_set<int> trapPosition;
	TrapSquare * getTrapSquare(int trapSquareNumber);
	void generateUniqueColumnNumbers(int numberOfElements); // allows traps to have unique columns & rows

	//display functions
	void setupRowHeadingsDisplay(string& location, string cellDivider, vector<vector<string>>& cellLines);
	void setupColumnHeadingsDisplay(string& location, string cellDivider, string & columnHeader);
	void setupBoardDisplay(string cellDivider, vector<vector<string>>& cellLines);
	void draw(int numberOfPlayers);


public:
	//Constructor
	Board(int rows = 6, int columns = 9, int numPlayers = 6, int numberOfPlayerHedgehogs = 4, int numberOfTraps=5);

	// Hedgehog Functionality
	int addHedgehog(pair<int,int> location, Hedgehog* playerHedgehog);
	int addHedgehog(int row, int column, Hedgehog* playerHedgehog);
	int removeHedgehog(pair<int, int> location);
	int removeHedgehog(int row, int column);
	
	// Square Functionality
	vector<Square*> getRow(int row);
	vector<Square*> getColumn(int column);
	Square* getSquare(int row, int column);
	Square* getSquare(pair<int, int>);
	int getColumns() { return columns; }
	int getRows() { return rows; }

	// Player Functionality
	int getHedgeHogsPerPlayer() { return hedgeHogsPerPlayer; };
	int setNumberofPlayers(int numPlayers) { numberOfPlayers = numPlayers; return 0; };

	// Additional Trap Functionality
	void setTrapCount(int num) { numberOfTraps = num; };
	int getTrapCount() { return numberOfTraps; };
	void increaseTrapCount() { numberOfTraps++; };

	// Display Functionality
	int display();
};

#endif /* BOARD_H */