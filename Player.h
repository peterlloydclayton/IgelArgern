/*
a. File Name: Player.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: header file for the Player


*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <map>
#include "Hedgehog.h"
#include "Color.h"

using namespace std;

class Player {
private:
	int playerId;
	COLORS color;
	vector<Hedgehog*> hedgehogs;
	int activeHedgehogs;

public:
	// Constructors & Destructors
	Player(int id, COLORS col, int hedgeHogNumber = 4);
	Player(const Player&);	// copy constructor

	// State information for player
	int GetId() { return playerId; };
	COLORS GetColor() { return color; };
	string GetColorString();

	// Hedgehog related information
	vector<Hedgehog*> getHedgehogs();
	Hedgehog * getHedgehog(int hh) { return hedgehogs[hh]; };
	int getNumberOfHedgeHogs() { return hedgehogs.size(); }

	// Location processing behaviors
	int chooseTrack(vector<int> listOfAvailableTracks);	// during initial Hedgehog setup
	int chooseTrack();									// during initial Hedgehog setup
};

#endif /* PLAYER_H */
