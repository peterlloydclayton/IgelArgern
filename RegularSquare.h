/*
a. File Name: RegularSquare.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: header file for the RegularSquare

*/

#ifndef REGULARSQUARE_H
#define REGULARSQUARE_H

#include <string>
#include <stack>
#include <iterator>
#include "Hedgehog.h"
#include "Square.h"

using namespace std;

// RegularSquare class
class RegularSquare : public Square {
protected:
    stack<Hedgehog*> hedgehogs;
    // enum to store the type of regular square
    enum {
        Start = 0,
        Normal = 1,
        End = 2
    };
    enum {Rtypes = 3};
private:
    static string pt[Rtypes]; // string equivs of Regular square types
    int Regular_type;
public:
    // Constructors
    RegularSquare() : Square(), Regular_type(Start) { square_type = "Regular"; }
    RegularSquare(string name, int x, int y, int t = Start): Square(name, x, y), Regular_type(t){ square_type = "Regular"; }
    RegularSquare(const RegularSquare&); // copy constructor
    RegularSquare& operator = (const RegularSquare& t); // assignment operator

    // Hedgehog functionality
	void addHedgehog(Hedgehog* h);
    Hedgehog* removeHedgehog();
    Hedgehog* getTopHedgehog();
    vector<Hedgehog*> getAllHedgehogs();

    // Info
    string getType();

    // Display functionality
    string display();
    void displaySquareDetails();
};

#endif /* REGULARSQUARE_H */
