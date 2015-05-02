#pragma once

#include <string>
#include <vector>
#include <memory>
#include "render/texture.h"

///
/// utilities.h defines miscellanious helpful methods. All methods are namespaced in the "utils" namespace.
///

namespace utils
{

/// ----------------------------------------------------------------------------------------------
/// Time related utilities
///
///
/// Gets the current time since the linux epoch, in milliseconds. Return type is an
/// unsigned long long to ensure enough bits of precision in the returned value.
///
unsigned long long getCurrentTimeMillis();

/// ----------------------------------------------------------------------------------------------
/// Random number related utilities
///

///
/// Seeds the random number generator with the system time. This will only seed the random number generator the first time it's called; doing nothing on
/// subsequent calls.
///
void seedRandomGenerator();
///
/// Generates a pseudo random integer value from somewhere in the range from 0 to (maxValue - 1).
/// \return a pseudo-random number from 0 to (maxValue - 1) inclusive.
///
int getRandomInt(int maxValue);
///
/// Generates a float value from 0 to 1 inclusive.
///
float getRandomFloat();

/// ----------------------------------------------------------------------------------------------
/// String utilities
/// 

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
double parseDouble(const std::string& s);
float parseFloat(const std::string& s);
int parseInt(const std::string& s);

/// ----------------------------------------------------------------------------------------------
/// File utilities
///

///
/// Reads the contents of a text file into a std::string. Throws std::runtime_error if the file fails to open.
///
std::string readTextFile(std::string filepath);
///
/// Writes the contents of an std::string to fail. Throws std::runtime_error if the file fails to open.
///
void writeTextFile(std::string filepath, std::string contents);
///
/// Reads the contents of a text file, adding each line as a separate string in a vector.
///
std::vector<std::string> readTextFileAsLines(std::string filepath);
///
/// Builds a filepath using the OS dependent resource directory and then appending the provided path. 
/// For example, on windows the OS dependent directory might be C:/Program Files/Engine 
///
std::string buildPath(std::string path);

/// ----------------------------------------------------------------------------------------------
/// Texture utilities
///
std::shared_ptr<Texture> getTexture(std::string);

/// ----------------------------------------------------------------------------------------------
/// Colours utilities
///
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




}








