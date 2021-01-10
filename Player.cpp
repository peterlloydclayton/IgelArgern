/*
a. File Name: Player.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for the player.  Contains a vector of hedgehogs

*/

#include "Player.h"

// Constructor
Player::Player(int id, COLORS col,int hedgeHogNumber)
{
	playerId = id;
	color = col;
	activeHedgehogs = hedgeHogNumber;
	hedgehogs.resize(activeHedgehogs);

	// initialize the hedgehog vector
	int i = 0;
	for (auto iter = hedgehogs.begin();iter != hedgehogs.end();iter++) {
		*iter = new Hedgehog(playerId, color);
		i++;
	}
}

// Copy Constructor
Player::Player(const Player& p)
{
	playerId = p.playerId;
	color = p.color;
	activeHedgehogs = p.activeHedgehogs;
	//hedgehogs;
	int i = 0;
	for (auto iter = p.hedgehogs.begin(); iter != p.hedgehogs.end(); iter++) {
		hedgehogs[i]=(*iter);

		i++;
	}
}

// Return all the hedgehogs belonging to the player
vector<Hedgehog*> Player::getHedgehogs()
{
	return hedgehogs;
}

// choose a track for the game play
int Player::chooseTrack()
{
	int track;
	cout << "Player "<<playerId<<", Please Choose A Track: ";

	cin >> track;
	
	return track;
}

// get the player color as a string
string Player::GetColorString()
{
	return Color::getColor(color) ;
}

// choose a random track for the game logic
int Player::chooseTrack(vector<int> availableTracks)
{
	int track = rand() % availableTracks.size();

	cout << "Player " << playerId << ", Please Choose A Track: ";

	return availableTracks[track];
}
