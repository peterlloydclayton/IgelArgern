/*
a. File Name: Game.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: header file for the Game

*/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream> 
#include <iostream>
#include "Player.h"
#include "Square.h"
#include "Board.h"


using namespace std;

class Game {
private:
	// Main Game Board
	Board board;

	// Player Attributes
	vector<Player*> players;
	list<int> playerIds;
	int numberOfPlayers;
	int currentPlayerId;
	Player* winner =0;
	map<Player*, int> playerResults;

	// Hedgehog Attributes & Methods
	int hedgehogCreationCount=0;
	int hedgehogsNeededToWin = 3;
	Hedgehog * getChosenHedgehog(int track);		
	vector<Hedgehog*> getMovableHedgehogs(vector<Square*> &track);
	bool CheckPreviousSpacesForHedghogs(pair<int, int> currentLocation);

	// Internal Functions: Setting up the Initial Hedgehog placement for each player
	vector<int> availablePositions;						// list of remaining spaces to choose from
	vector<vector<int>> hedgeHogLayers;					// part of the hedgehog placement matrix
	vector<int> displayAvailableStartTracks(int row);	// list of remaining spaces to choose from
	bool hasEmptySpaces(int row);						// verifies if there are emptyspaces
	void setupPlayerHedgehogs();						// main for placing player hedgehogs using the hedgehog placement matrix
	void setupHedgehogPlacementMatrix();				// main logic for creating the hedgehog placement matrix
	void chooseHedgehogTrack(Player * p, int row);		// Determining where to add the hedgehog on the board. Also, adds hedgehog to the board

	// Evaluating Track Selection for moving a player hedgehog forward
	bool validateTrackSelection(int track);

public:
	Game() : numberOfPlayers(4),currentPlayerId(-1) {};	// Constructor
	Game(int numberOfPlayers, int currentPID=-1);		// Constructor
	~Game();											// Destructor

	void start(bool verbose = false);					// Choose To Turn On/Off cout display functionality

	// Player methods related to the game
	vector<Player*> getPlayers() { return players; };
	int getNumberOfPlayers() { return numberOfPlayers; };
	void setPlayer(int index, int iD, COLORS c);		// create/update new player in the player vector
	void addPlayers(vector<Player*>& newPlayers);		// set the current player vector to the values of a new player vector (implemented during initiliazation)

	// Core Game Logic
	int rollDice();			// PLAYER MOVE 1
	pair<int, int> processSideStep(Player* currentPlayer);		// PLAYER MOVE 2
	pair<int, int> processPlayerMove(Player& currentPlayer, int currentTrack);	// PLAYER MOVE 3
	bool processLastColumn();	// EVALUATE ROUND
	void displayResults();		// DISPLAY THE FINAL RESULTS

	// Winner & Final Results Accessors
	Player* getWinner() { return winner; };
	map<Player*, int> getGameResults() { return  playerResults;; };
};

#endif /* GAME_H */