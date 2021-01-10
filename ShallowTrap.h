/*
a. File Name: ShallowTrap.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the ShallowTrap

*/

#ifndef SHALLOWTRAP_H
#define SHALLOWTRAP_H

#include <string>
#include <stack>
#include <iterator>
#include "Hedgehog.h"
#include "TrapSquare.h"

using namespace std;

// ShallowTrap class
class ShallowTrap : public TrapSquare {
private:
    Hedgehog *trappedHedgehog;   // to store the first trapped Hedgehog
    bool noTrappedHedgehog = true;
    stack<Hedgehog*> movableHedgehogs;
public:
    // Constructors
    ShallowTrap(): TrapSquare() { square_type = "Shallow"; }
    ShallowTrap(string name, int x, int y): TrapSquare(name, x, y){ square_type = "Shallow"; }

    // Hedgehog Functionality
    void addHedgehog(Hedgehog *h);
    Hedgehog *removeHedgehog();
    void removeTrappedHedgehog();
    bool hasTrappedHedgehog() { return !noTrappedHedgehog; };
    Hedgehog* getTrappedHedgehog() { return trappedHedgehog; };
    void addTrappedHedgehog(Hedgehog* h) { addHedgehog(h);noTrappedHedgehog = false; };
    Hedgehog* getTopHedgehog();

    // Display Functionality
    void showTrappedHedgehog();
    string display();
    void displaySquareDetails();
};

#endif /* SHALLOWTRAP_H */