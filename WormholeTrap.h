/*
a. File Name: WormholeTrap.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the WormholeTrap

*/

#ifndef WORMHOLETRAP_H
#define WORMHOLETRAP_H

#include <string>
#include <array>
#include <iterator>
#include "Hedgehog.h"
#include "TrapSquare.h"

using namespace std;

// WormholeTrap class
class WormholeTrap : public TrapSquare {
    Hedgehog *trappedHedgehog;
    bool hasHedgehog = false;
public:
    // Constructors
    WormholeTrap(): TrapSquare() { square_type = "Wormhole"; }
    WormholeTrap(string name, int x, int y): TrapSquare(name, x, y){ square_type = "Wormhole"; }

    // Hedgehog Functionality
	void addHedgehog(Hedgehog *h);
    Hedgehog *removeHedgehog();
    Hedgehog* getTopHedgehog();

    // Display Functionality
    string display();
    void displaySquareDetails();
};

#endif /* WORMHOLETRAP_H */