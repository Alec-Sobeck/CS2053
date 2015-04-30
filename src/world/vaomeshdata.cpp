#include "world/vaomeshdata.h"

VAOMeshData::VAOMeshData(
		std::string associatedTextureName,
		int numVerts,
		float *vertices,
		int verticesSize,
		float *normals,
		int normalsSize,
		float *colours,
		int coloursSize,
		float *textures,
		int texturesSize,
		gl::GLenum glRenderMode,
		std::shared_ptr<Material> material
	) 
	: associatedTextureName(associatedTextureName), glRenderMode(glRenderMode), numVerts(numVerts), vertices(vertices), verticesSize(verticesSize), normals(normals), normalsSize(normalsSize),
	colours(colours), coloursSize(coloursSize), textures(textures), texturesSize(texturesSize), material(material)
{
}

AABB VAOMeshData::getAABB()
{
    if(numVerts <= 0)
    {
        return AABB(0, 0, 0, 0, 0, 0);
    }
    float xMin = vertices[0];
	float xMax = vertices[0];
	float yMin = vertices[1];
	float yMax = vertices[1];
	float zMin = vertices[2];
	float zMax = vertices[2];

    //xMin
    for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 0] < xMin)
        {
            xMin = vertices[i * 3 + 0];
        }
    }
    //xMax
	for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 0] > xMax)
        {
			xMax = vertices[i * 3 + 0];
        }
    }
    //yMin
	for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 1] < yMin)
        {
			yMin = vertices[i * 3 + 1];
        }
    }
    //yMax
	for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 1] > yMax)
        {
			yMax = vertices[i * 3 + 1];
        }
    }
    //zMin
	for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 2] < zMin)
        {
			zMin = vertices[i * 3 + 2];
        }
    }
    //zMax
	for (int i = 0; i < numVerts; i++)
    {
		if (vertices[i * 3 + 2] > zMax)
        {
			zMax = vertices[i * 3 + 2];
        }
    }

    return AABB(xMin, yMin, zMin, xMax, yMax, zMax);
}


