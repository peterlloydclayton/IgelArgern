/*
a. File Name: main.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: main program for the Igel Argern Game

*/

#include <iostream>
#include "GameDriver.h"
#include "ArcadeSimulation.h"

int main() {
    
    // Repeat Program Loop
    string keepGoing = "";
    while (keepGoing != "n") {

        // Decide between Arcade Mode & Single Game Mode
        int choice = 0;
        while ((choice != 1) && (choice != 2)) {
            cout << "Please Choose: Single Game (1)" << endl;
            cout << "Please Choose: Arcade Simulation (2)" << endl;
            cin >> choice;
        }

        // Single Game Mode Chosen
        if (choice == 1) {
            GameDriver gd;
            gd.startSingleGame();
        }
        // Arcade Mode Chosen
        else if (choice == 2) {
            ArcadeSimulation test;
            test.initialize();
            test.status();
        }

        // Repeat Program Loop
        cout << "Would you like to continue?" << endl;
        cin >> keepGoing;
    }
    return 0;
}