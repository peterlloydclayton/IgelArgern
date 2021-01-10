/*
a. File Name: NormalTrap.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the NormalTrap

*/

#ifndef NORMALTRAP_H
#define NORMALTRAP_H

#include <string>
#include <stack>
#include <iterator>
#include "Hedgehog.h"
#include "TrapSquare.h"

using namespace std;

// NormalTrap class
class NormalTrap : public TrapSquare {
private:
    stack<Hedgehog*> trappedHedgehogs;
public:
    // Constructors
	NormalTrap(): TrapSquare() { square_type = "Normal"; }
    NormalTrap(string name, int x, int y): TrapSquare(name, x, y){ square_type = "Normal"; }

    // Hedgehog functionality
	void addHedgehog(Hedgehog *h);
    Hedgehog* removeHedgehog();
    Hedgehog* getTopHedgehog();

    // Display functionality
    string display();
    void displaySquareDetails();
};

#endif /* NORMALTRAP_H */
