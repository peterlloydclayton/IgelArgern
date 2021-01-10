/*
a. File Name: TrapSquare.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019, Xcode (For Sereysathia)
e. Brief Description of the file: implementation file for the TrapSquare header
*/

#include <stdio.h>
#include "TrapSquare.h"
#include <iostream>
using namespace std;


// function to return get trap type
string TrapSquare::trapType(){
    return Square::square_type;
}
