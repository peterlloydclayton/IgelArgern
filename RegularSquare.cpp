/*
a. File Name: RegularSquare.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: implementation file for the RegularSquare header
*/

#include <stdio.h>
#include "RegularSquare.h"
#include <iostream>
using namespace std;

string RegularSquare::pt[RegularSquare::Rtypes] = {"Start", "Normal", "End"};

RegularSquare::RegularSquare(const RegularSquare& r) {
    hedgehogs = r.hedgehogs;
    pt[Rtypes] = r.pt[Rtypes];
    Regular_type = r.Regular_type;
} // copy constructor

RegularSquare& RegularSquare::operator = (const RegularSquare& r) {
    hedgehogs = r.hedgehogs;
    pt[Rtypes] = r.pt[Rtypes];
    Regular_type = r.Regular_type;
    return *this;
} // assignment operator

// Function that add Hedgehog to stack
void RegularSquare::addHedgehog(Hedgehog *h){
    hedgehogs.push(h);
}

// Function to get and remove Hedgehog
Hedgehog * RegularSquare::removeHedgehog(){
    Hedgehog* temp;
    if (hedgehogs.empty()) {
        temp = nullptr;
        return temp;
    }else {
        cout << "Remove Successful" << endl;
        Hedgehog* temp = hedgehogs.top();    // store the top of the stack in temp
        hedgehogs.pop();    // remove the top of the stack
        return temp;
    }
}

// Function to get the type of RegularSquare
string RegularSquare::getType() {
    return pt[Regular_type];
}

Hedgehog* RegularSquare::getTopHedgehog()
{
    if (hedgehogs.empty()) {
        return nullptr;
    }
    else {
        return hedgehogs.top();
    }
}

// Retrieve all the hedgehogs for the square
vector<Hedgehog*> RegularSquare::getAllHedgehogs() {
    stack<Hedgehog*> hhTempStack = hedgehogs;
    vector<Hedgehog*> temp;
    for (int i = 0; i < hhTempStack.size();i++) {
        Hedgehog* hh = hhTempStack.top();
        hhTempStack.pop();
        temp.push_back(hh);
    }

    return temp;
}

// Displays Square info for placement on the board
string RegularSquare::display() {
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = hedgehogs;
    if (temp.empty()) {
        displayString = "";
        displayString.append("*");
    }
    else {
        displayString = "+" + temp.top()->getHedgehogInfo();
    }
    return displayString;
}

// Function to display Hedgehogs in Square
void RegularSquare::displaySquareDetails(){
    cout << label << "(" << location.first << "," << location.second << "," << pt[Regular_type] << "):";
    // declare temporary hedgehog stack
    stack<Hedgehog*> temp = hedgehogs;
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