
#include <glm/vec3.hpp>
#include "utils/flexarray.h"
#include "terrainrenderer.h"

TerrainRenderer::TerrainRenderer() : terrainPolygons(FlexArray<TerrainPolygon>(100)), vbo(new DynamicVBO())
{
}

void TerrainRenderer::create(std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture)
{
    std::shared_ptr<FlexArray<TerrainPolygon>> polys = terrain->getPolygons();
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
