/*
a. File Name: ArcadeSimulation.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Header file for the Timing Wheel

*/


#ifndef TimingWheel_h
#define TimingWheel_h

#include "Partition.h"
using namespace std;

int const MAX_DELAY = 10;

// TimingWheel class
class TimingWheel {
private:
    Partition* slot[MAX_DELAY + 1];
    int current_slot;
    int simulation_time;
    int player_count = 0;

public:
    // Constructor
    TimingWheel() : current_slot(0), simulation_time(MAX_DELAY) {
        for (int i = 0; i < MAX_DELAY; i++) {
            slot[i] = nullptr;
        }
    }
    int getCurrSlot();
    void setCurrSlot(int s);
    void setSimulationtime(int t);
    void insert(int play_time, GameTable* gt);
    void schedule();
    void print();
    void clear_curr_slot();
    
    friend ostream& operator <<(std::ostream& output, TimingWheel const& tw);
};

#endif /* TimingWheel_h */