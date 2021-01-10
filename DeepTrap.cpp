/*
a. File Name: DeepTrap.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: Implementation file for the DeepTrap header

*/

#include <stdio.h>
#include <iostream>
#include "DeepTrap.h"

// Function to add Hedgehog
void DeepTrap::addHedgehog(Hedgehog *h){
    // Only add hedgehog less than the pit size - if pit is full, will not add and should REMOVE the front 
    if(trappedHedgehogs.size() < qSize)
        trappedHedgehogs.push(h);
}

// Function to remove Hedgehog for Deep Pit
Hedgehog* DeepTrap::removeHedgehog(){
    Hedgehog* temp = nullptr;
    if(trappedHedgehogs.size() == qSize){
        temp = trappedHedgehogs.front(); // store the hedgehog at the front of the queue
        trappedHedgehogs.pop(); // remove the front hedgehog
    }
    return temp;
}

// Function to get the Depth of the Deep Pit
int DeepTrap::getDepth(){
    return qSize;
}

// Display functionality for the board
string DeepTrap::display() {
    if (trappedHedgehogs.empty())
    {
        displayString = "";
        displayString.append("Empty");
    }
    else {
        // declaring a temporary queue to store the trapped Hedgehogs
        queue<Hedgehog*> temp = trappedHedgehogs;
        displayString = temp.front()->getHedgehogInfo(); // display the front
    }
    return displayString;
}

// Function to display for Deep Pit
void DeepTrap::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << square_type << "):";
    if(trappedHedgehogs.empty())
        cout << " **X**\n";
    else{
        // declaring a temporary queue to store the trapped Hedgehogs
        queue<Hedgehog*> temp = trappedHedgehogs;
        while(!temp.empty()){
            temp.front()->displayHedgehog(); // display the front
            temp.pop(); // pop the front out
        }
    }
}

Hedgehog* DeepTrap::getTopHedgehog()
{
    if (trappedHedgehogs.empty()) {
        return nullptr;
    }
    else {
        return trappedHedgehogs.front();
    }
}