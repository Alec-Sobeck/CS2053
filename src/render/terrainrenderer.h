#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include <memory>
#include <glm/vec3.hpp>
#include "graphics/camera.h"
#include "graphics/terrainpolygon.h"
#include "terrain/terraindata.h"
#include "render/dynamicvbo.h"
#include "utils/flexarray.h"
#include "render/texture.h"

class TerrainRenderer
{
public:
    FlexArray<TerrainPolygon> terrainPolygons;
    DynamicVBO* vbo;
    TerrainRenderer();
    void create(std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture);
	void draw(Camera *cam);
    ~TerrainRenderer();
};






#endif
