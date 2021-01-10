/*
a. File Name: DeepTrap.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the DeepTrap

*/

#ifndef DEEPTRAP_H
#define DEEPTRAP_H

#include <string>
#include <queue>
#include <iterator>
#include "Hedgehog.h"
#include "TrapSquare.h"

using namespace std;

// DeepTrap class
class DeepTrap : public TrapSquare {
private:
    queue<Hedgehog*> trappedHedgehogs;
    int qSize;  // Size of Queue - Depth
public:
    // Constructors
    DeepTrap(): TrapSquare() { square_type = "Deep"; qSize = 5; }
    DeepTrap(string name, int x, int y, int s = 5): TrapSquare(name, x, y), qSize(s) { square_type = "Deep"; }

    // Hedgehog Functionality
	void addHedgehog(Hedgehog *h);
    Hedgehog * removeHedgehog();
    Hedgehog* getTopHedgehog();

    // info
    int getDepth();

    // display functionality
    string display();
    void displaySquareDetails();
};

#endif /* DEEPTRAP_H */
