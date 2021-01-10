/*
a. File Name: BlackholeTrap.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: Implementation file for the BlackholeTrap header

*/

#include <stdio.h>
#include <iostream>
#include "BlackholeTrap.h"

// Function to add a Hedgehog to BlackholeTrap
void BlackholeTrap::addHedgehog(Hedgehog *h){
    trappedHedgehogs.push(h);
}

// Display functionality for the board
string BlackholeTrap::display() {
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

// Function to display for Blackhole Trap
void BlackholeTrap::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << square_type << "):";
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = trappedHedgehogs;
    if (temp.empty()){
        cout << " **X**\n";
    }
    else {
        while(!temp.empty()){
            temp.top()->displayHedgehog();
            temp.pop();
        }
        cout << "Note: These hedgehog(s) are trapped and cannot be removed\n";
    }
}

Hedgehog* BlackholeTrap::getTopHedgehog()
{
    if (trappedHedgehogs.empty()) {
        return nullptr;
    }
    else {
        return trappedHedgehogs.top();
    }
}