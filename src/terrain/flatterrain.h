#pragma once

#include "terrain/terrain.h"

class FlatTerrain : public Terrain
{
    int size;
public:
	FlatTerrain(int size);
    float getHeight(double x, double y);
    utils::Colour getColour(double x, double y);
    void generateTerrain(int LoD, float size);
    std::shared_ptr<TerrainData> exportToTerrainData();
};
