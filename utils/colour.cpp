
#include <sstream>
#include "colour.h"


Colour::Colour(double r, double g, double b, double a) : r(r), g(g), b(b), a(a), name("undefined_colour_name")
{
}

Colour::Colour(std::string name, double r, double g, double b, double a) : r(r), g(g), b(b), a(a), name(name)
{
}

std::string Colour::toString()
{
	std::stringstream ss;
	ss << name << ": (" << r << "," << g << "," << b << "," << a << ")";
	return ss.str();
}

float Colour::getR()
{
	return r;
}

float Colour::getG()
{
	return g;
}

float Colour::getB()
{
	return b;
}

float Colour::getA()
{
	return a;
}

std::string Colour::getName()
{
	return name;
}