/*
a. File Name: Board.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for Board, used by the game class. The board is comprised of a vector of vector of Square pointers

*/

#include "Board.h"
#include <math.h>

// Constructor
Board::Board(int boardRows, int boardColumns, int numPlayers, int numberOfPlayerHedgehogs, int numOfTraps)
{
	rows = boardRows;
	columns = boardColumns;
	hedgeHogsPerPlayer = numberOfPlayerHedgehogs;
	numberOfPlayers = numPlayers;
	numberOfTraps = numOfTraps;

	//initialize 2 dimensional container, vector
	board.resize(rows);
	for (int i = 0; i < rows;i++) {
		board[i].resize(columns);
	}
	// Start Squares
	for (int i = 0;i < rows;i++) {
		board[i][0] = new RegularSquare();
		board[i][0]->setLocation(i+1, 0+1);
	}

	// Middle Squares
	generateUniqueColumnNumbers(columns); // create set of unique column numbers for trap squares in the vector of middle squares
	getMiddleSquares(rows, columns);

	// End Squares
	for (int i = 0;i < rows;i++) {
		int column = columns - 1;
		board[i][column] = new RegularSquare();
		board[i][column]->setLocation(i+1, columns);
	}
}

// Each trap must occupy a unique column.  This function creates a unique set of numbers based upon the number of columns on the board
// 3 columns are removed from consideration (The start square, the 2nd column, and the end square)
void Board::generateUniqueColumnNumbers(int columnCount)
{
	bool i = true;
	while (i) {
		int randNum = rand() % (columnCount - 3) + 2; // 3 represents the number columns removed from consideration. 2(3rd column) represents the valid starting column
		if (randNum < (columnCount - 1)) {
			trapPosition.insert(randNum);
		}

		if (trapPosition.size() == (columnCount - 3)) // once the unique set of numbers matches the number of viable fields, end the loop
			i = false;
	}
}

// logic for generating the middle squares
void Board::getMiddleSquares(int rows, int columns)
{
	auto trapItr = trapPosition.begin(); // to access the first value of the unordered set
	for (int i = 0;i < rows;i++) {
		int randomTrapSquare = rand() % numberOfTraps + 1; // create a random int selection for a trap

		for (int j = 1; j < columns - 1;j++)
		{
			if (j == *trapItr) {  // if the current column equals the random value in the unordered set, create a trap field
				board[i][j] = getTrapSquare(randomTrapSquare);
				board[i][j]->setLocation(i+1,j+1);
			}
			else {
				board[i][j] = new RegularSquare();
				board[i][j]->setLocation(i+1, j+1);
			}
		}
		trapItr++; // move the iterator forward to access the next value in the unordered set
	}
}

// Trap square creation
TrapSquare * Board::getTrapSquare(int trapSquareNumber) {
	switch (trapSquareNumber)
	{
		case 1:
			return new NormalTrap();
		case 2:
			return new ShallowTrap();
		case 3:
			return new DeepTrap();
		case 4:
			return new WormholeTrap();
		case 5:
			return new BlackholeTrap();
		default:
			return new NormalTrap();
			break;
	}
}

// output all of the locations on the board
void Board::draw(int numberOfPlayers)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << board[i][j]->getLocation().first << ", " << board[i][j]->getLocation().second <<" ";
		}
		cout << endl;
	}
}

// adds a hedgehog as a pair<row,column>
int Board::addHedgehog(pair<int, int> location, Hedgehog * playerHedgehog)
{
	int row,column;
	row = location.first;
	column = location.second;
	addHedgehog(row, column, playerHedgehog);
	return 0;
}

// adds a hedgehog as a row/column
int Board::addHedgehog(int row, int column, Hedgehog* playerHedgehog)
{
	playerHedgehog->setLocation(row, column);
	board[row][column]->addHedgehog(playerHedgehog);
	return 0;
}

// removes a hedgehog as a pair<int,int>
int Board::removeHedgehog(pair<int, int> location)
{
	int row, column;
	row = location.first;
	column = location.second;
	removeHedgehog(row, column);
	return 0;
}

// removes a hedgehog as a row/column
int Board::removeHedgehog(int row, int column)
{
	if (board[row][column]->removeHedgehog() == nullptr)cout<<"No HedgeHogs to Remove!"<<endl;
	return 0;
}

// create the row headings to append to the first entry of every row
void Board::setupRowHeadingsDisplay(string & location, string cellDivider, vector<vector<string>> & cellLines) {
	// Add Row Headings
	for (int i = 0;i < rows;i++) {
		string blankSpace;
		pair<int, int> cellLocation = board[i][0]->getLocation();
		location = "Track: " + to_string(cellLocation.first);
		//format the cell location data
		int extraLocationSpaces = cellWidth - (int)location.length();

		for (int i = 0;i < extraLocationSpaces;i++)
			location.append(" ");

		for (int i = 0;i < cellWidth;i++)
			blankSpace.append(" ");

		if (i == columns - 1)
			cellDivider = "";

		cellLines[i][0].append(location + cellDivider);
		cellLines[i][1].append(blankSpace + cellDivider);
	}
}

// create the column headings to add to the first row of the grid
void Board::setupColumnHeadingsDisplay(string& location, string cellDivider, string & columnHeader) {
	columnHeader = "";
	// Add Column Headings
	for (int j = -1;j < columns;j++) {

		if (j == -1)
			location = "";
		else {
			pair<int, int> cellLocation = board[0][j]->getLocation();
			location = "Column: " + to_string(cellLocation.second);
		}
		//format the cell location data
		int extraLocationSpaces = cellWidth - (int)location.length();

		for (int i = 0;i < extraLocationSpaces;i++)
			location.append(" ");

		if (j == columns - 1)
			cellDivider = "";

		columnHeader.append(location + cellDivider);
	}

}

// generate the board for display
// each cell has a column for the Square type and for the current hedgehog on the square
void Board::setupBoardDisplay(string cellDivider, vector<vector<string>>& cellLines) {

	for (int i = 0; i < rows;i++) {
		cellDivider = " | ";
		for (int j = 0;j < columns;j++) {
			string hedgeHogInfo= (*board[i][j]).display();

			string cellName = ((string)typeid(*board[i][j]).name()).substr(6);
			string addSpaces = "";

			int extraNameSpaces = cellWidth - (int)cellName.length();		//format the the length of the cell
			int extraHedgehogSpaces = cellWidth - hedgeHogInfo.length();	//format the the length of the cell

			for (int i = 0;i < extraNameSpaces;i++)
				cellName.append(" ");

			for (int i = 0;i < extraHedgehogSpaces;i++)
				hedgeHogInfo.append(" ");

			if (j == columns - 1)
				cellDivider = "";

			cellLines[i][0].append(cellName + cellDivider);
			cellLines[i][1].append(hedgeHogInfo + cellDivider);
		}
	}
}


/*
	Print the Matrix of Squares
	Each cell of the matrix of squares contains multiple lines of information.
		to achieve a grid effect, we capture information from the entire row and store in one string
		we then print each of the rows of the strings and are able to achieve a grid effect
*/
int Board::display()
{
	vector<vector<string>> cellLines(rows);			// The matrix for the display grid
	string location;
	string cellDivider = " | ";
	string columnHeader;

	// Create The Number of Rows for Each Cell of the Display Grid
	for (int i = 0; i < rows;i++) {
		cellLines[i].resize((2 + numberOfPlayers));
	}

	cout << endl;
	setupRowHeadingsDisplay(location, cellDivider, cellLines);			// Add Row Headings
	setupColumnHeadingsDisplay(location, cellDivider, columnHeader);	// Add Column Headings
	setupBoardDisplay(cellDivider, cellLines);							// setup the main board cells for printing
	cout << columnHeader << endl;										// Print column headers
	for (int i = 0; i < rows;i++) {										// Print each row of the display grid
		cout << cellLines[i][0] << endl;
		cout << cellLines[i][1] << endl;
	}
	return 0;
}

// return a square based on row/colum
Square * Board::getSquare(int row, int column)
{
	return board[row][column];
}

// return a square based on a location pair<int,int>
Square * Board::getSquare(pair<int, int> location)
{
	return getSquare(location.first,location.second);
}

// return a row of squares based on a row number
vector<Square*> Board::getRow(int row) {
	vector<Square*> temp = board[row];
	temp.pop_back(); // omit the last column of the row (it's the end square)
	return temp;
}

// return a column of squares based on a column number
vector<Square*> Board::getColumn(int column) {
	vector<Square*> columns;
	for (auto iter = board.begin(); iter != board.end(); iter++) {
		columns.push_back((*iter)[column]);
	}
	return columns;
}