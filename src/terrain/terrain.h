#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "utils/colour.h"
#include "terrain/terraindata.h"
#include "utils/flexarray.h"

class Terrain
{
public:
	int lod;
	float width;
	FlexArray<glm::vec3> vertices;
	FlexArray<Colour> colours;
	FlexArray<glm::vec2> uvs;
	FlexArray<glm::vec3> normals;
	virtual void generateTerrain(int LoD, float size);
	virtual std::shared_ptr<TerrainData> exportToTerrainData();
	virtual float getHeight(double x, double y) = 0;
	virtual Colour getColour(double x, double y) = 0;
};


#endif
