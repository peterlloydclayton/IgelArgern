/*
a. File Name: GameTable.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for GameTable, used by Arcade Simulation and GameDriver.  Collects info on the winner of the game, game stats, and game id

*/

#include "GameTable.h"

// randomly generate player colors
unordered_set<COLORS> GameTable::generateUniquePlayerColors()
{
    unordered_set<COLORS> randomColors;

    bool i = true;
    int numberOfColors = Color::getNumberOfColors();
    while (i) {
        int randNum = rand() % (numberOfColors); 
        if (randNum < (numberOfColors)) {
            randomColors.insert((COLORS)randNum);
        }

        if (randomColors.size() == numberOfColors) // once the unique set of numbers matches the number of viable fields, end the loop
            i = false;
    }

    return randomColors;
}

// Create Initialize players with colors and IDs
vector<Player*> GameTable::createPlayers()
{
    Game *IAGame = new Game(playerNum);
    int PlayerId;
    unordered_set<COLORS> randomColors = generateUniquePlayerColors();
    auto colorItr = randomColors.begin();
    string playerDisplayString = "";

    // Create a player based on the number of players registered with the Game
    for (int i = 0; i < playerNum; i++)
    {
        PlayerId = rand() % 100 + 1;        //reset the playerId for the game
        IAGame->setPlayer(i, PlayerId, *colorItr);
        colorItr++;     // increment the color iterator to cycle through to the next color

        //create an output string for the players created
        string id = to_string(IAGame->getPlayers()[i]->GetId());
        string color = IAGame->getPlayers()[i]->GetColorString();
        playerDisplayString += "(" + id + ": " + color +") ";
    }

    cout << "Players in the Game: "<< IAGame->getPlayers().size()<<": "<<playerDisplayString<<endl;

    return IAGame->getPlayers();
}

// start game without setting the number of players (this will use a random number of players)
// Verbose in the last line represents whether or not to display information when running the game class
// Verbose acts like light switch for displaying/not displaying cout output to the console
void GameTable::startGame(bool verbose) {
    int numOfPlayers = 0;
    while ((numOfPlayers < 2))
        numOfPlayers = (rand() % 7);    // choose a random number of players between 2 and 6

    startGame(numOfPlayers, verbose);
}

// Start the game logic from the Game object
void GameTable::startGame(int numPlayers, bool verbose)
{
    playerNum = numPlayers;
    gm = Game(playerNum);
    vector<Player*> temp = createPlayers(); //create players and to a player vector
    gm.addPlayers(temp);        // add the newly created players to the game object
    gm.start(verbose);          // start the game object
}
