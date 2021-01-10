/*
a. File Name: Square.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the Square

*/

#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <stack>
#include <vector>
#include <iterator>
#include "Hedgehog.h"

using namespace std;

// Square - abstract Base Class
class Square {
    protected:
        string displayString;
        string label;
        string square_type;
		pair<int, int> location;
	public:
        // Constructors
        Square();
        Square(string name, int x, int y);
        Square(const Square&); // copy constructor

        // Square Type
        virtual string getSquareType() { return square_type; };
        
        // Hedgehog functionality
        virtual void addHedgehog(Hedgehog *h) = 0;  // pure virtual method
        virtual Hedgehog* removeHedgehog() = 0; // pure virtual method
        virtual Hedgehog * getTopHedgehog() = 0;  // pure virtual method
        virtual vector<Hedgehog*> getAllHedgehogs() { return vector<Hedgehog*>(); };  // pure virtual method
        virtual bool hasTrappedHedgehog() { return false; }; // pure virtual method
        virtual Hedgehog * getTrappedHedgehog() { return nullptr; }; // pure virtual method

        // Location
        pair<int, int> getLocation();
        void setLocation(int x, int y);
        
        // Display
        virtual string display() = 0;     // pure virtual method
};

#endif /* SQUARE_H */
