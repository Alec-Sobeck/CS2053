#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "utils/colour.h"
#include "terrain/terraindata.h"

class Terrain
{
protected:
	int lod;
	float width;
	std::vector<glm::vec3> vertices;
	std::vector<Colour> colours;
	std::vector<glm::vec2> uvs;

public:
	virtual void generateTerrain(int LoD, float size);
	virtual TerrainData exportToTerrainData();
	virtual float getHeight(double x, double y) = 0;
	virtual Colour getColour(double x, double y) = 0;
};


#endif