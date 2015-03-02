#ifndef ENG_FLAT_TERRAIN_H
#define ENG_FLAT_TERRAIN_H

#include "utils/colour.h"
#include "terrain/terrain.h"

class FlatTerrain : public Terrain
{
    int size;
public:
	FlatTerrain(int size);
    float getHeight(double x, double y);
    Colour getColour(double x, double y);
    void generateTerrain(int LoD, float size);
    std::shared_ptr<TerrainData> exportToTerrainData();
};

#endif
