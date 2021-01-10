/*
a. File Name: BlackholeTrap.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the BlackholeTrap

*/

#ifndef BLACKHOLETRAP_H
#define BLACKHOLETRAP_H

#include <string>
#include <stack>
#include <iterator>
#include "Hedgehog.h"
#include "TrapSquare.h"

using namespace std;

// BlackholeTrap class - Note: there is no removeHedgehog() because trapped hedgehogs are removed from board
class BlackholeTrap : public TrapSquare {
private:
    stack<Hedgehog*> trappedHedgehogs;    // to store trapped hedgehogs FOREVER!
public:
    // Constructors
    BlackholeTrap(): TrapSquare() { square_type = "Blackhole"; }
    BlackholeTrap(string name, int x, int y): TrapSquare(name, x, y){ square_type = "Blackhole"; }

    // Hedgehog Functionality
    void addHedgehog(Hedgehog *h);
    Hedgehog* removeHedgehog() { return nullptr; };
    Hedgehog* getTopHedgehog();

    // Display Functionality
    string display();
    void displaySquareDetails();
};

#endif /* BLACKHOLETRAP_H */
