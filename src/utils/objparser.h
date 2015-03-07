#ifndef ENG_OBJECT_PARSER_H
#define ENG_OBJECT_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "world/meshdata.h"
#include "terrain/terraindata.h"
#include "graphics/model.h"

class ObjParser
{
public:
    std::vector<std::shared_ptr<MeshData>> meshes;
	std::string fileName;
	std::string textureName;
	std::string modelName;
	ObjParser(std::string fileName, std::string textureName);
	std::shared_ptr<Model> exportModel();
//	std::shared_ptr<TerrainData> exportTerrain();
private:
    void loadData();
};



#endif
