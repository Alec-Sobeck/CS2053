
#include <glm/vec3.hpp>
#include "terrainrenderer.h"

TerrainRenderer::TerrainRenderer(std::shared_ptr<Shader> terrainShader, std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture) 
{
	this->texture = terrainTexture;
	std::shared_ptr<std::vector<TerrainPolygon>> polys = terrain->getPolygons();

	int vertexCount = 0;
	for (int i = 0; i < polys->size(); i++)
	{
		vertexCount += polys->at(i).vertexCount();
	}	
	float *rawVertexData = new float[vertexCount * 3];
	float *rawColourData = new float[vertexCount * 4];
	float *rawTextureData = new float[vertexCount * 2];
	int index = 0;
	for (int i = 0; i < polys->size(); i++)
	{
		TerrainPolygon *p = &polys->at(i);
		RawPolygonData f = p->getRawData();
		for (int j = 0; j < f.numVerts; j++, index++)
		{
			rawVertexData[index * 3 + 0]  = f.data[j * 12 + 0];
			rawVertexData[index * 3 + 1]  = f.data[j * 12 + 1];
			rawVertexData[index * 3 + 2]  = f.data[j * 12 + 2];
			rawColourData[index * 4 + 0]  = f.data[j * 12 + 6];
			rawColourData[index * 4 + 1]  = f.data[j * 12 + 7];
			rawColourData[index * 4 + 2]  = f.data[j * 12 + 8];
			rawColourData[index * 4 + 3]  = f.data[j * 12 + 9];
			rawTextureData[index * 2 + 0] = f.data[j * 12 + 10];
			rawTextureData[index * 2 + 1] = f.data[j * 12 + 11];
		}
	}
	
	vao = std::shared_ptr<TexturedColouredVAO>(new TexturedColouredVAO(
		terrainShader->programID, vertexCount, rawVertexData, sizeof(float) * vertexCount * 3, 
		rawColourData, sizeof(float) * vertexCount * 4, rawTextureData, sizeof(float) * vertexCount * 2
	));

	delete[] rawVertexData;
	delete[] rawColourData;
	delete[] rawTextureData;
}

void TerrainRenderer::draw()
{
	texture->bind();
    vao->draw();
}

TerrainRenderer::~TerrainRenderer()
{
}
