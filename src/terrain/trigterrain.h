#ifndef TRIG_TERRAIN_H
#define TRIG_TERRAIN_H

#include "terrain.h"
#include "utils/colour.h"

class TrigTerrain : public Terrain
{
public:
	TrigTerrain(int lod, float size);
	float getHeight(double x, double y);
	Colour getColour(double x, double y);
};

#endif