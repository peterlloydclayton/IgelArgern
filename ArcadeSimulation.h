/*
a. File Name: ArcadeSimulation.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Header class for Arcade Simulation: Initiates Aracade's TimeWheel

*/

#ifndef ArcadeSimulation_h
#define ArcadeSimulation_h

#include <string>
#include "TimingWheel.h"
#include "GameTable.h"

using namespace std;

int const MAX_TABLES = 3;

class ArcadeSimulation {
    int simulation_time; // duration of simulation time
    string filename; // output file name
    TimingWheel TW;     // Timing Wheel
    GameTable tables[MAX_TABLES];   // array of all the game tables in operation

public:
    ArcadeSimulation(int t = 0, string n = "");

    // Core Arcade Logic
    void initialize();  
    void status();

    // accessors and mutators
    void set_simulationTime(int t);
    void set_filename(string n);
    int get_simulationTime();
    string get_filename();
};

#endif /* ArcadeSimulation_h */
