#include <iostream>
#include "flatterrain.h"

FlatTerrain::FlatTerrain(int size) : size(size)
{
    generateTerrain(5, size);
}

float FlatTerrain::getHeight(double x, double y)
{
    return 0.0f;
}

utils::Colour FlatTerrain::getColour(double x, double y)
{
	return utils::Colour(1, 1, 1, 1);
}

void FlatTerrain::generateTerrain(int LoD, float size)
{
	lod = LoD;
	if(lod < 3)
        lod = 3;
	width = size;

	float step = width / lod;
	int numVerts = lod * lod;

	vertices = std::vector<glm::vec3>(numVerts);
	colours = std::vector<utils::Colour>(numVerts);
	uvs = std::vector<glm::vec2>(numVerts);
	normals = std::vector<glm::vec3>(4);
	for (int i = 0; i < lod; i++)
	{
		for (int j = 0; j < lod; j++)
		{
			float x = (i * step) - width / 2;
			float z = (j * step) - width / 2;
			vertices[i * lod + j] = glm::vec3(x, getHeight(x, z), z);
			utils::Colour colour = getColour(x, z);
			colours[i * lod + j] = colour;
		}
	}
	std::cout << numVerts << std::endl;
	uvs[0] = glm::vec2(1, 1);
	uvs[1] = glm::vec2(0, 1);
	uvs[2] = glm::vec2(0, 0);
	uvs[3] = glm::vec2(1, 0);
	normals[0] = glm::vec3(0, 1, 0);
	normals[1] = glm::vec3(0, 1, 0);
	normals[2] = glm::vec3(0, 1, 0);
	normals[3] = glm::vec3(0, 1, 0);
}

std::shared_ptr<TerrainData> FlatTerrain::exportToTerrainData()
{
	std::vector<glm::vec3> vertices = this->vertices;
	std::vector<glm::vec3> normals;
	std::vector<utils::Colour> colours = this->colours;
	std::vector<glm::vec2> textureCoords = this->uvs;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;

	for (int i = 0; i < static_cast<int>(vertices.size()) - lod; i++)
	{
		if (i % lod == 0)
        {
            continue;
		}
		faceVerts.push_back(glm::vec3(i, i + 1, i + lod));
		faceVerts.push_back(glm::vec3(i + 1, i + 1 + lod, i + lod));
		faceTextures.push_back(glm::vec3(1, 2, 3));
		faceTextures.push_back(glm::vec3(1, 2, 3));
		faceNormals.push_back(glm::vec3(1, 2, 3));
		faceNormals.push_back(glm::vec3(1, 2, 3));
	}

	return std::shared_ptr<TerrainData>(new TerrainData(vertices, normals, colours, textureCoords, faceVerts, faceNormals, faceTextures));
}
