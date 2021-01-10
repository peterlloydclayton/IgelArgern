/*
a. File Name: ArcadeSimulation.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 05/07/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for the Timing Wheel: creates the Arcade Loop and cycles through all game table plays until finished

*/

#include <iostream>
#include "Partition.h"
#include "TimingWheel.h"

// function to get the current slot
int TimingWheel::getCurrSlot() {
    return this->current_slot;
}

// function to set the current slot
void TimingWheel::setCurrSlot(int s) {
    this->current_slot = s;
}

void TimingWheel::setSimulationtime(int t) {
    this->simulation_time = t;
}

// function to insert a gametable at a time slot
void TimingWheel::insert(int play_time, GameTable* gt) {
    Partition* pt = new Partition(gt);
    if (slot[play_time] == NULL) {
        slot[play_time] = pt;
    }
    else {
        pt->set_Next_Partition(slot[play_time]);
        slot[play_time] = pt;
    }
}

// function to schedule
void TimingWheel::schedule() {

    cout << "Schedule: " << endl;
    cout << "simulation time: " << simulation_time << endl << endl;

    int time_instance = current_slot;
    int temp = simulation_time;

    // Simulate the Player the game with the given simulation time
    while (simulation_time) {
        cout << "---------------------------" << endl;
        cout << "time instance = " << time_instance << endl;
        cout << "---------------------------" << endl;
        if (slot[time_instance % MAX_DELAY] == NULL && time_instance == 0) {
            cout << "Starting...\n" << endl;
        }
        else if (slot[time_instance % MAX_DELAY] == NULL && time_instance > 0) {
            cout << "All Game Table are busy playing\n" << endl;
        }
        else {
            Partition* p;
            p = slot[time_instance % MAX_DELAY];
            GameTable* table;
            while (p != NULL)
            {
                table = p->get_GameTable();
                cout << "Table ID: " << table->getTablenum() << endl;
                // Print the Winner of the previous Game

                cout << "New round: " << endl;
                table->startGame();

                // get the players who are going to play the Game
                cout << "\tplayers: " << table->getPlayersCount() << endl;
                player_count += table->getPlayersCount();   // count the number of players

                // get the new time for when the game will finished
                int time = (table->getPlayersCount() + time_instance) % MAX_DELAY;
                cout << " \tfinished time: " << time << endl;

                // insert gameTable at a new time
                insert(time, table);
                p = p->get_Next_Partition();

                table->startGame();

                // insert a new random number of players between 2-6 to the table when game is done
                int randPlayer;
                randPlayer = rand() % (6 - 2 + 1) + 2;
                table->setPlayerCount(randPlayer);

            }
            clear_curr_slot();

            cout << endl;
        }
        time_instance++;
        simulation_time--;   // schedule for the next time slot
    }
    simulation_time = temp;

}

// function to clear the current time slot
void TimingWheel::clear_curr_slot() {
    slot[current_slot] = NULL;
    current_slot = (current_slot + 1) % MAX_DELAY;
}

// Loop through all of the Timing Wheel Slots and print the current partitions to the console
void TimingWheel::print() {
    int i = 0;
    cout << "For simulation time: " << simulation_time << endl;
    cout << "Timing Wheel: " << endl;

    for (int j = 0;j < MAX_DELAY;j++) { //sizeof(slot)-1
        cout << "t = " << i++ << ": ";
        if (slot[j] != NULL) {
            Partition* pt = slot[j]->get_Next_Partition();
            cout << slot[j]->get_GameTable()->getTablenum() << " -> ";
            while (pt != NULL) {
                cout << pt->get_GameTable()->getTablenum() << " -> ";
                pt = pt->get_Next_Partition();
            }
            cout << "null\n";
        }
        else
            cout << "Empty" << endl;
    }

    cout << endl;

    cout << "Total number of Players: " << player_count << endl;
}

// Loop through all of the Timing Wheel Slots and print the current partitions to a file
ostream& operator <<(std::ostream& os, TimingWheel const& tw)
{

    int i = 0;
    os << "For simulation time: " << tw.simulation_time << endl;
    os << "Timing Wheel: " << endl;
    for (int j = 0;j < MAX_DELAY;j++) {//(Partition* s : tw.slot) {
        os << "t = " << i++ << ": ";
        if (tw.slot[j] != NULL) {
            Partition* pt = tw.slot[j]->get_Next_Partition();
            os << tw.slot[j]->get_GameTable()->getTablenum() << " -> ";
            while (pt != NULL) {
                os << pt->get_GameTable()->getTablenum() << " -> ";
                pt = pt->get_Next_Partition();
            }
            os << "null\n";
        }
        else
            os << "Empty" << endl;
    }
    os << endl;

    os << "Total number of Players: " << tw.player_count << endl;

    return os;
}