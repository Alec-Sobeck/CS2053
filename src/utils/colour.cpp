
#include <sstream>
#include "colour.h"

Colour::Colour() : r(0), g(0), b(0), a(0)//, name("undefined_colour_name")
{
}

Colour::Colour(double r, double g, double b, double a) : r(r), g(g), b(b), a(a)//, name("undefined_colour_name")
{
}

//Colour::Colour(std::string name, double r, double g, double b, double a) : r(r), g(g), b(b), a(a)//, name(name)
//{
//}

/*
Colour::Colour(const Colour& other) : r(other.r), g(other.g), b(other.b), a(other.a), name(other.name)
{
}
*/

std::string Colour::toString()
{
	std::stringstream ss;
	ss /*<< name*/ << ": (" << r << "," << g << "," << b << "," << a << ")";
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

/*
std::string Colour::getName()
{
	return name;
}
*/
/*
Colour& Colour::operator=(const Colour &otherColour)
{
    Colour other(otherColour);
    std::swap(r, other.r);
    std::swap(g, other.g);
    std::swap(b, other.b);
    std::swap(a, other.a);
    //std::stringstream ss;
    //ss << other.name;
    //std::string temp = ss.str();
    //name = ss.str();
    std::swap(name, other.name);
    return *this;
}
*/

