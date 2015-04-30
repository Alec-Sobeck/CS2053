#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glbinding/gl/gl.h>
#include "math/physics/aabb.h"
#include "world/material.h"

class VAOMeshData
{
public:
	std::string associatedTextureName;
	int numVerts;
	float *vertices;
	int verticesSize;
	float *normals;
	int normalsSize;
	float *colours;
	int coloursSize;
	float *textures;
	int texturesSize;
	gl::GLenum glRenderMode;
	std::shared_ptr<Material> material;

	VAOMeshData(
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
    );
	///
	/// This calculates every time.
	/// \return an AABB that bounds the entire Model. If for some reason there is no vertex data the bounding box will simply be the origin.
	///
	AABB getAABB();
};
