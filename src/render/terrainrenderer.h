#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include <vector>
#include "graphics/camera.h"
#include "graphics/terrainpolygon.h"
#include "terrain/terraindata.h"
#include "render/dynamicvbo.h"
#include "render/texture.h"
#include "render/vao.h"
#include "shaders/shader.h"

class TerrainRenderer
{
public:
    std::shared_ptr<TexturedColouredVAO> vao;
	std::shared_ptr<Texture> texture;
	TerrainRenderer(std::shared_ptr<Shader> terrainShader, std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture);
	void draw();
    ~TerrainRenderer();
};



