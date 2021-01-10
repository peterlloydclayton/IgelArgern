/*
a. File Name: Color.h
b. Author: Harika Para, Sereysathia Luy, Peter Clayton
c. Date: 03/27/2020
d. Compiler Used: Visual Studio 2019
e. Brief Description of the file: header file for the Color.h
*/

#ifndef COLOR_H
#define COLOR_H

#include <map>
#include <string>

using namespace std;

enum class COLORS {
	RED=0,
	YELLOW=1,
	BLUE=2,
	ORANGE=3,
	GREEN=4,
	PURPLE=5
};

static class Color {
	private:
		static map<COLORS, string> gameColors;
		static int numberOfColors;
	public:
		Color() {};
		static string getColor(int color);
		static string getColor(COLORS color);
		static int getNumberOfColors();
};

#endif /* COLOR_H */
