/*
a. File Name: Hedgehog.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the Hedgehog
*/

#ifndef HEDGEHOG_h
#define HEDGEHOG_h

#include <string>
#include "Color.h"

using namespace std;

// Hedgehog class
class Hedgehog {
private:
	int playerId;
	string color;
    pair<int, int> currentLocation;
public:
    Hedgehog();                                 // Constructor
    Hedgehog(int id , string color);            // Constructor
    Hedgehog(int id, COLORS color);             // Constructor
    Hedgehog(const Hedgehog&);                  // Copy Constructor
    ~Hedgehog();                                // Destructor
    Hedgehog operator=(const Hedgehog& h);      // operator= overloading

    // Hedgehog info
    int getPlayerId();
    string getColor();
    string getHedgehogInfo();
    
    // Hedgehog location
    pair<int, int> getLocation() { return currentLocation; };
    void setLocation(int row, int column);

    // Display Hedgehog info
    void displayHedgehog();

};

#endif /* HEDGEHOG_h */
