/*
a. File Name: ArcadeSimulation.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for Arcade Simulation: Initiates Aracade's TimeWheel

*/
#include <iostream>
#include <fstream>

#include "ArcadeSimulation.h"
#include "TimingWheel.h"
#include "GameTable.h"

ArcadeSimulation::ArcadeSimulation(int t, string n) : simulation_time(t), filename(n) {
    // Initialize All The Game Tables For Arcade
    for (int i = 0; i < MAX_TABLES; i++) {
        tables[i] = GameTable(i + 1, 0);
    }
}

// Initialize function
void ArcadeSimulation::initialize() {
    string name;
    int time;

    cout << "Welcome to Igel Argen Game Arcade!" << endl;
    cout << "Please Enter the name of the output file you want to store the result: ";
    cin >> name;

    set_filename(name);


    cout << "Please enter the duration of simulation: ";
    cin >> time;

    set_simulationTime(time);

    // set the number of players in the 3 game tables
    for (int i = 0; i < MAX_TABLES; i++) {
        // insert the tables to the timing Wheel
        GameTable* p = &(tables[i]);
        TW.insert(1, p);
    }

    // set the simulation time for Timing Wheel
    TW.setSimulationtime(simulation_time);

}

// Core Arcade Logic
void ArcadeSimulation::status() {
    // display result to the screen
    TW.schedule();
    cout << "Number of Game Tables: " << MAX_TABLES << endl;
    TW.print();
    // open output file
    ofstream myfile(filename);
    myfile << "Number of Game Tables: " << MAX_TABLES << endl;
    myfile << TW;
}

// Accessors & Mutators
int ArcadeSimulation::get_simulationTime() {
    return simulation_time;
}

void ArcadeSimulation::set_simulationTime(int t) {
    simulation_time = t;
}

string ArcadeSimulation::get_filename() {
    return filename;
}

void ArcadeSimulation::set_filename(string n) {
    filename = n;
}