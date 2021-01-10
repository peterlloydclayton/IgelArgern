/*
a. File Name: WormholeTrap.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: Implementation file for the WormholeTrap header

*/

#include <iostream>
#include "WormholeTrap.h"

// Function to add Hedgehog for Wormhole
void WormholeTrap::addHedgehog(Hedgehog *h){
    trappedHedgehog = h;
    hasHedgehog = true;
}

// Function to remove Hedgehog for Wormhole
Hedgehog * WormholeTrap::removeHedgehog(){
    hasHedgehog = false;
    return trappedHedgehog;
}

// Display functionality for the board
string WormholeTrap::display() {
    if (hasHedgehog == true) {
        displayString = "ZAP";
    }
    else
        displayString = "Empty";

    return displayString;
}


// Function to display for Wormhole
void WormholeTrap::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << square_type << "):\n";
    if(hasHedgehog == true){
        trappedHedgehog->displayHedgehog();
    }else
        cout << " ** No hedgehog **\n";
}

Hedgehog* WormholeTrap::getTopHedgehog()
{
	return nullptr;
}