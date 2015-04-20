
#include <glm/vec3.hpp>
#include "terrainrenderer.h"

TerrainRenderer::TerrainRenderer() : terrainPolygons(std::vector<TerrainPolygon>(100)), vbo(new DynamicVBO())
{
}

void TerrainRenderer::create(std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture)
{
	std::shared_ptr<std::vector<TerrainPolygon>> polys = terrain->getPolygons();
    vbo->create(polys, terrainTexture);
}

void TerrainRenderer::draw(Camera *cam)
{
    vbo->draw(cam);
}

TerrainRenderer::~TerrainRenderer()
{
    delete vbo;
}
