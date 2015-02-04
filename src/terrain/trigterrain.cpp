
#include <cmath>
#include "trigterrain.h"
#include "terrain.h"
#include "utils/colour.h"

TrigTerrain::TrigTerrain(int lod, float size)
{
	generateTerrain(lod, size);
}

float TrigTerrain::getHeight(double x, double y) 
{
	return (float)(4 + sin(x*.1) * cos(y*.1) * 4);
}

Colour TrigTerrain::getColour(double x, double y) 
{
	return Colour(getHeight(x, y) / 8, .5 - getHeight(x, y) / 8, 0, 1);
}


