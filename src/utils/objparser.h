#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "world/meshdata.h"
#include "terrain/terraindata.h"
#include "graphics/model.h"
#include "world/material.h"

class ObjParser
{
public:
    std::vector<std::shared_ptr<VAOMeshData>> meshes;
    std::map<std::string, std::shared_ptr<Material>> materials;
    std::string filePath;
	std::string fileName;
	std::string textureName;
	std::string modelName;
	ObjParser(std::string filePath, std::string fileName, std::string textureName, bool dataIsTriangles);
	std::shared_ptr<Model> exportModel();
//	std::shared_ptr<TerrainData> exportTerrain();
private:
    void loadData(bool dataIsTriangles);
};


