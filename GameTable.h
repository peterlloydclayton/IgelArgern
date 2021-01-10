/*
a. File Name: GameTable.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Header file for GameTable, used by Arcade Simulation and GameDriver.  Collects info on the winner of the game, game stats, and game id

*/

#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "Player.h"
#include "Square.h"
#include "Board.h"
#include "Game.h"

using namespace std;

class GameTable {
private:
	Game gm;
	int TableId;
	int playerNum;
	map<Player*, int> playerResults;
	Player* winner = 0;
	unordered_set<COLORS> generateUniquePlayerColors();	// used to generate random colors for players in the game

public:
	// Constructor
	GameTable(int i = 0, int p = 0) : TableId(i), playerNum(p) {}

	// TableId
	int getTablenum() { return TableId; }

	// Player Information
	vector<Player*> createPlayers();
	int getPlayersCount() { return playerNum; }
	void setPlayerCount(int n) { playerNum = n; }

	// Start the game
	void startGame(int numPlayers, bool verbose=false);
	void startGame(bool verbose = false);

	// Final Game Results
	Player* getWinner() { return gm.getWinner(); };
	map<Player*, int> getGameResults() { return gm.getGameResults(); };
};

#endif /* GAMETABLE_H */
