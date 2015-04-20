
#include <sstream>
#include "colour.h"

Colour::Colour() : r(0), g(0), b(0), a(0)
{
}

Colour::Colour(double r, double g, double b, double a) : r(r), g(g), b(b), a(a)
{
}

std::string Colour::toString()
{
	std::stringstream ss;
	ss << "(" << r << "," << g << "," << b << "," << a << ")";
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