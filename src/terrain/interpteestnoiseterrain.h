#ifndef INTERP_TEST_NOISE_TERRAIN_H
#define INTERP_TEST_NOISE_TERRAIN_H

#include "utils/flexarray.h"
#include "utils/colour.h"
#include "terrain/terrain.h"

class InterpTestNoiseTerrain : public Terrain
{
private:
	std::shared_ptr<Flex2D<float>> heightMap;
	float maxVal;
public:
	InterpTestNoiseTerrain(int numVal, float maxVal, int lod, float size);
    std::shared_ptr<Flex2D<float>> buildNoise(int width);
	float getHeight(double x, double y);
    Colour getColour(double x, double y);
};

#endif
