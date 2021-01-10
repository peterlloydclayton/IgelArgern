/*
a. File Name: Color.cpp
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: Implementation file for the Color.h
*/

#include "Color.h"

map<COLORS, string> Color::gameColors = {
	{COLORS::RED,"RED"},
	{COLORS::YELLOW,"YELLOW"},
	{COLORS::BLUE,"BLUE"},
	{COLORS::ORANGE,"ORANGE"},
	{COLORS::GREEN,"GREEN"},
	{COLORS::PURPLE,"PURPLE"}
};

int Color::numberOfColors = 6;

string Color::getColor(int color)
{
	return gameColors[(COLORS)color];
}

string Color::getColor(COLORS color)
{
	return gameColors[color];
}

int Color::getNumberOfColors()
{
	return numberOfColors;
}
