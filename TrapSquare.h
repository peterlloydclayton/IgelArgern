/*
a. File Name: TrapSquare.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the TrapSquare

*/

#ifndef TRAPSQUARE_H
#define TRAPSQUARE_H

#include <string>
#include <stack>
#include <queue>
#include <iterator>
#include "Hedgehog.h"
#include "Square.h"

using namespace std;

// TrapSquare - abstract class
class TrapSquare : public Square {
public:
    // Constructors
    TrapSquare(): Square() {}
    TrapSquare(string name, int x, int y): Square(name, x, y) {}

    // Hedgehog Functionality
	virtual void addHedgehog(Hedgehog *h) = 0; // pure virtual method
    virtual Hedgehog* getTopHedgehog() = 0;
    
    // Info
    string trapType();

    // Display functionality
    virtual string display() = 0; // pure virtual method
};

#endif /* TRAPSQUARE_H */