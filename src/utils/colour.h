#pragma once

#include <string>

class Colour
{
public:
	double r;
	double g;
	double b;
	double a;
	Colour();
	Colour(double r, double g, double b, double a);
	std::string toString();
	float getR();
	float getG();
	float getB();
	float getA();
};

const Colour RED(1, 0, 0, 1);
const Colour GREEN(0, 1, 0, 1);
const Colour WHITE(1, 1, 1, 1);
const Colour CRITICAL(1, 0.5, 0, 1);
const Colour BLUE(0 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 1);
const Colour GRAY(153.0 / 255.0, 153.0 / 255.0, 153.0 / 255.0, 1);
const Colour SEMI_DARK_GRAY(102.0 / 255.0, 102.0 / 255.0, 102.0 / 255.0, 1);
const Colour DARK_GRAY(64.0 / 255.0, 64.0 / 255.0, 64.0 / 255.0, 1);
const Colour LIGHT_GREEN(152.0 / 255.0, 251.0 / 255.0, 152.0 / 255.0, 1);
const Colour LIME_GREEN(50.0 / 255, 205.0 / 255, 50.0 / 255, 1);
const Colour FIERY1(255.0 / 255, 253.0 / 255, 24.0 / 255, 1);
const Colour FIERY2(253.0 / 255, 124.0 / 255, 5.0 / 255, 1);
const Colour FIERY3(253.0 / 255, 181.0 / 255, 9.0 / 255, 1);
const Colour FIERY4(255.0 / 255, 117.0 / 255, 4.0 / 255, 1);
const Colour FIERY5(255.0 / 255, 69.0 / 255, 0.0 / 255, 1);
const Colour YELLOW(255.0 / 255, 255.0 / 255, 51.0 / 255, 1);
const Colour BLACK(0, 0, 0, 1);
// A somewhat peach-like color that is nearly white.
const Colour VARDEN(255.0 / 255, 248.0 / 255, 220.0 / 255, 1);
const Colour DARK_BROWN(31.0 / 255, 18.0 / 255, 9.0 / 255, 1);
const Colour BROWN(131.0 / 255, 76.0 / 255, 28.0 / 255, 1);
const Colour MIDNIGHT_BLUE(0.0 / 255, 51.0 / 255, 102.0 / 255, 1);
const Colour ALPHA(1, 1, 1, 0);
const Colour LIGHT_BLUE(102.0 / 255.0, 153.0 / 255.0, 255.0 / 255.0, 1);
// A moderately dark blue.
const Colour MARINER(51.0 / 255.0, 102.0 / 255.0, 204.0 / 255.0, 1);
// A somewhat dark shade of blue.
const Colour AZURE(51.0 / 255.0, 102.0 / 255.0, 153.0 / 255.0, 1);

#pragma once
