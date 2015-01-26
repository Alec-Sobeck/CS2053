
#include "terrain.h"
#include "terrain/terraindata.h"

void Terrain::generateTerrain(int LoD, float size)
{
	lod = LoD;
	width = size;

	float step = width / lod;
	int numVerts = lod * lod;

	vertices = std::vector<glm::vec3>();
	vertices.reserve(numVerts);
	colours = std::vector<Colour>();
	colours.reserve(numVerts);
	uvs = std::vector<glm::vec2>();
	uvs.reverse(numVerts);
	for (int i = 0; i < lod; i++)
	{
		for (int j = 0; j < lod; j++)
		{
			float x = (i * step) - width / 2;
			float z = (j * step) - width / 2;
			vertices[i*lod + j] = glm::vec3(x, getHeight(x, z), z);
			colours[i*lod + j] = getColour(x, z);
		}
	}
	uvs[0] = glm::vec2(1, 1);
	uvs[1] = glm::vec2(0, 1);
	uvs[2] = glm::vec2(0, 0);
	uvs[3] = glm::vec2(1, 0);

}

TerrainData Terrain::exportToTerrainData()
{
	std::vector<glm::vec3> vertices = this->vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours = this->colours;
	std::vector<glm::vec2> textureCoords = this->uvs;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;

	for (int i = 0; i < static_cast<int>(vertices.size()) - lod; i++)
	{
		if (i % lod == 0) continue;

		faceVerts.push_back(glm::vec3(i, i + 1, i + lod));
		faceVerts.push_back(glm::vec3(i + 1, i + 1 + lod, i + lod));

		faceTextures.push_back(glm::vec3(1, 2, 3));
		faceTextures.push_back(glm::vec3(1, 2, 3));
	}

	return TerrainData(vertices, normals, colours, textureCoords, faceVerts, faceNormals, faceTextures);
}