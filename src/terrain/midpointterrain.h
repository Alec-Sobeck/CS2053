#ifndef MIDPOINT_TERRAIN_H
#define MIDPOINT_TERRAIN_H

#include "utils/colour.h"
#include "terrain/terrain.h"

class MidPointTerrain : public Terrain
{
private:
	float initialValue;
	float roughness;
	float randomizerValue = 7;
	int sideLength;
	float maxHeight = 0.1f;

public:
    FlexArray<FlexArray<float>> heightMap;
	MidPointTerrain(int iterations, float roughness, int lod, float size);
	void buildHeightMap(float randomizerValue, int x1, int y1, int x2, int y2);
    float getHeight(double x, double y);
    Colour getColour(double x, double y);
};

#endif
