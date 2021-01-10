/*
a. File Name: ArcadeSimulation.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for the Partition which occupies each slot of the Timing Wheel

*/



#ifndef Partition_h
#define Partition_h

#include "GameTable.h"

// Partition class
class Partition {
private:
    GameTable* gameTable_pointer=0;
    Partition* next_Partition=0;

public:
    // constructors
    Partition() {};
    Partition(GameTable*& gt) : gameTable_pointer(gt), next_Partition(nullptr) {
    }
    Partition(GameTable*& gt, Partition* nextp) : gameTable_pointer(gt), next_Partition(nextp) {}

    // copy constructor
    Partition(const Partition& n) : gameTable_pointer(n.gameTable_pointer), next_Partition(n.next_Partition) {}

    // destructor
    ~Partition() {}

    // accessors to get data
    GameTable* get_GameTable() { return this->gameTable_pointer; }
    Partition* get_Next_Partition() { return this->next_Partition; }

    // mutators to set data
    void set_GameTable(GameTable* gtp) { this->gameTable_pointer = gtp; }
    void set_Next_Partition(Partition* nextp) { this->next_Partition = nextp; }

    // operator= overloading
    Partition operator=(Partition& n) {
        gameTable_pointer = n.gameTable_pointer;
        next_Partition = n.next_Partition;
        return (*this);
    }

};


#endif /* Partition_h */
