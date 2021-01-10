/*
 a. File Name: Square.cpp
 b. Author: Harika Para, Sereysathia Luy, Peter Clayton
 c. Date: 03/27/2020
 d. Compiler Used: Visual Studio 2019 , Xcode (For Sereysathia)
 e. Brief Description of the file: implementation file for the Square header
 */

#include <stdio.h>
#include "Square.h"
#include <iostream>
using namespace std;

// Square default constructor
Square::Square(){
    label = "";
    location.first = 0;
    location.second = 0;
}

Square::Square(const Square& h)   // copy constructor
{
    displayString = h.displayString;
    label = h.label;
    square_type = h.square_type;
    location = h.location;
}   


// Square non-default constructor
Square::Square(string name, int x, int y){
    label = name;
    location.first = x;
    location.second = y;
}

// Function to get location
pair<int, int> Square::getLocation(){
    return location;
}

// Function to set location
void Square::setLocation(int x, int y){
    location.first = x;
    location.second = y;
}


