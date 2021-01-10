/*
a. File Name: ShallowTrap.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: Implementation for the ShallowTrap header

*/

#include <stdio.h>
#include <iostream>
#include "ShallowTrap.h"

// Function to add Hedgehog into ShallowTrap
void ShallowTrap::addHedgehog(Hedgehog *h){
    // check to see if empty - YES, put it in the trap and it is not empty
    if(noTrappedHedgehog == true){
        trappedHedgehog = h;
        noTrappedHedgehog = false;
    }else
        movableHedgehogs.push(h); // if NO, add it into a stack
}

// Function to remove Hedgehog from ShallowTrap
Hedgehog* ShallowTrap::removeHedgehog(){
    Hedgehog* temp = nullptr;
    // if there is a trapped hedgehog and there is a hedgehog on top - you can remove from the stack
    if(noTrappedHedgehog == false && !movableHedgehogs.empty()){
        temp = movableHedgehogs.top();    // store the top of the stack in temp
        movableHedgehogs.pop();    // remove the top of the stack
    }
    return temp;
}

void ShallowTrap::removeTrappedHedgehog() {
    Hedgehog temp;
    // if there is a trapped hedgehog and there are no hedgehogs on top - you can transfer the hedgehog to the stack
    if (noTrappedHedgehog == false && movableHedgehogs.empty()) {
        movableHedgehogs.push(trappedHedgehog);    // remove the top of the stack
        trappedHedgehog = new Hedgehog();
        noTrappedHedgehog == true;
    }
}

// Function to SHOW the trapped hedgehog
void ShallowTrap::showTrappedHedgehog(){
    trappedHedgehog->displayHedgehog();
}

// Display functionality for the board
string ShallowTrap::display() {
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = movableHedgehogs;
    // If temp is empty and there is no hedgehog trapped
    if (temp.empty() && noTrappedHedgehog == true) {
        displayString="";
        displayString.append("Empty");
    }
    else {
        if (getTopHedgehog() == nullptr){
            displayString = "TRAPPED: " + to_string(trappedHedgehog->getPlayerId());
        }else {
            string freeHedgehog = temp.top()->getHedgehogInfo();
            displayString = "+" + freeHedgehog;
        }

    }
    return displayString;
}

// Function to Display for ShallowTrap
void ShallowTrap::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << square_type << "):";
        // declare temporary hedgehog stack
        stack<Hedgehog*> temp = movableHedgehogs;
        // If temp is empty and there is no hedgehog trapped
        if (temp.empty() && noTrappedHedgehog == true){
            displayString = "";
            cout << "Empty";
        }
        else {
            while(!temp.empty()){
                temp.top()->displayHedgehog();
                temp.pop();
            }
            showTrappedHedgehog(); // display the trapped hedgehog
        }
    
}

Hedgehog* ShallowTrap::getTopHedgehog()
{
    if (movableHedgehogs.empty()) {
        return nullptr;
    }
    else {
        return movableHedgehogs.top();
    }
}