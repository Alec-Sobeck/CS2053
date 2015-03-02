#ifndef ENG_OBJECT_PARSER_H
#define ENG_OBJECT_PARSER_H

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "world/modeldata.h"
#include "terrain/terraindata.h"

class ObjParser
{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;
	std::string fileName;
	std::string textureName;
	std::string modelName;
	ObjParser(std::string fileName, std::string textureName);
	ModelData exportModel();
	std::shared_ptr<TerrainData> exportTerrain();
private:
    void loadData();
};



#endif
