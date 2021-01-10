/*
a. File Name: NormalTrap.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: Implementation file for the NormalTrap header

*/

#include <stdio.h>
#include <iostream>
#include "NormalTrap.h"

// Function to add Hedgehog for Normal Trap
void NormalTrap::addHedgehog(Hedgehog *h){
    trappedHedgehogs.push(h);
}

// Function to remove Hedgehog for Normal Trap
Hedgehog* NormalTrap::removeHedgehog(){
    Hedgehog* temp = trappedHedgehogs.top(); // store top Hedgehog with in stack
    trappedHedgehogs.pop(); // remove top Hedgehog in stack
    return temp;
}

// Display functionality for the board
string NormalTrap::display() {
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = trappedHedgehogs;
    if (temp.empty()) {
        displayString = "";
        displayString.append("Empty");
    }
    else {
        displayString = "-" + temp.top()->getHedgehogInfo();
    }
    return displayString;
}

// Function to display for Normal Trap
void NormalTrap::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << square_type << "):";
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = trappedHedgehogs;
    if (temp.empty()){
        cout << " **X**";
    }
    else {
        while(!temp.empty()){
            temp.top()->displayHedgehog();
            temp.pop();
        }
    }
}

Hedgehog* NormalTrap::getTopHedgehog()
{
    if (trappedHedgehogs.empty()) {
        return nullptr;
    }
    else {
        return trappedHedgehogs.top();
    }
}