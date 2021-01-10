/*
a. File Name: GameDriver.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Single Game Mode: Runs 1 round of Igel Argern

*/
#include "GameDriver.h"

using namespace std;

int GameDriver::startSingleGame()
{
    int numberOfPlayers = 0;
    int rounds = 1;

    cout << "Welcome To IgelArgern Single Game Mode!\n" << endl;

    // Choose a Random Number of Players
    char chooseNumberOfPlayers;
    cout << "Would you like to choose the number of players? (y or n)" << endl;
    cin >> chooseNumberOfPlayers;

    // User Chosen Number of Players
    if (tolower(chooseNumberOfPlayers) == 'y'){
        while ((numberOfPlayers<2) || (numberOfPlayers > 6)) {
            cout << "Please Choose a Number between 2 and 6" << endl;
            cin >> numberOfPlayers;
        }
    // Random Number of Players
    }else {
        while ((numberOfPlayers < 2))
            numberOfPlayers = (rand() % 7);
    }

    cout << "How many iterations would you like to run?" << endl;
    cin >> rounds;

    cout << "The first round will have: " << numberOfPlayers << ", players" << endl;
    cout << "The game will run for "<<rounds<<" rounds" << endl;
   
    GameTable gmTable;
    char displayChoice;       // Decided whether or not output program details to the screen
    bool verbose = false;       // Verbose acts as an on/off switch for displaying program details

    cout << "\nWould you like to display output? (y or n)" << endl;
    cin >> displayChoice;
    if (tolower(displayChoice) == 'y') verbose = true;

    // Cycle through all of the chosen number of rounds
    for (int i = 0; i < rounds;i++) {
        // Start the Game
        cout << "\n*****" << endl;
        cout << "*****" << endl;
        cout << "Round: " << i+1<<endl;

        gmTable.startGame(numberOfPlayers, verbose);

        numberOfPlayers = 0;
        while ((numberOfPlayers < 2))
            numberOfPlayers = (rand() % 7);
    }

    return 0;
}
