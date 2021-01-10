/*
a. File Name: Hedgehog.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: implementation file for the Hedgehog header
*/

#include <stdio.h>
#include "Hedgehog.h"
#include <iostream>
using namespace std;

// Hedgehog default constructor
Hedgehog::Hedgehog(){
    playerId = 0;
    color = "";
    currentLocation.first = -1;
    currentLocation.second = -1;
}

// Hedgehog constructor
Hedgehog::Hedgehog(int id, string c){
    playerId = id;
    color = c;
    currentLocation.first = 0;
    currentLocation.second = 0;
}

// Hedgehog constructor
Hedgehog::Hedgehog(int id, COLORS c) {
    playerId = id;
    color = Color::getColor((int)c);
    currentLocation.first = 0;
    currentLocation.second = 0;
}


// Hedgehog copy constructor
Hedgehog::Hedgehog(const Hedgehog& h): playerId(h.playerId), color(h.color), currentLocation(h.currentLocation){}

// Hedgehog destructor
Hedgehog::~Hedgehog() {}

// Function to get Player ID
int Hedgehog::getPlayerId(){
    return playerId;
}

string Hedgehog::getColor()
{
	return color;
}

// Function to display Hedgehog
void Hedgehog::displayHedgehog(){
    cout << "Color: " << color << ", ID: " << playerId << ", Location: (" << currentLocation.first << ","<<currentLocation.second<<")"<<endl;;
}

string Hedgehog::getHedgehogInfo() {
    return color + " : " + to_string(playerId);
}

void Hedgehog::setLocation(int row, int column)
{
	currentLocation.first = row;
    currentLocation.second = column;
}

// assignment operator= overloading
Hedgehog Hedgehog::operator=(const Hedgehog & h){
    playerId = h.playerId;
    color = h.color;
    currentLocation.first = h.currentLocation.first;
    currentLocation.second = h.currentLocation.second;
    return (*this);
}