#pragma once

#include <string>
#include <memory>
#include <vector>
#include <glbinding/gl/gl.h>
#include "math/physics/aabb.h"
#include "world/material.h"

///
/// Contains data to create a VBO to draw a model. That is, vertex data, normals, colour, and texture coordinates.
///
class MeshData
{
public:
	const std::string associatedTextureName;
	const gl::GLenum glRenderMode;
	const int stride;
	const int vertexSize;
	const int vertexOffset;
	/// Corresponds to a GL constant type like GL_FLOAT, or GL_BYTE
	const gl::GLenum vertexType;
	const int normalSize;
	const int normalOffset;
	/// Corresponds to a GL constant type like GL_FLOAT, or GL_BYTE
	const gl::GLenum normalType;
	const int colourSize;
	const int colourOffset;
	/// Corresponds to a GL constant type like GL_FLOAT, or GL_BYTE
	const gl::GLenum colourType;
	const int textureCoordSize;
	const int textureCoordOffset;
	/// Corresponds to a GL constant type like GL_FLOAT, or GL_BYTE
	const gl::GLenum textureCoordType;
	/// The total number of elements associated to one vertex
	const int elementsPerRowOfCombinedData;
	std::vector<float> combinedData;
	const int vertexPerFace;
	bool hasTextureData;
    std::shared_ptr<Material> material;

	///
	/// Builds a new ModelData and disables textures.
	///
	MeshData(
			gl::GLenum glRenderMode,
			int vertexPerFace,
			int stride,
			int elementsPerRowOfCombinedData,
			int vertexSize, int vertexOffset, gl::GLenum vertexType,
			int normalSize, int normalOffset, gl::GLenum normalType,
			int colourSize, int colourOffset, gl::GLenum colourType,
			std::vector<float> combinedData
        );
	///
	/// Builds a new ModelData and enables textures
	///
	MeshData(
			gl::GLenum glRenderMode,
			std::shared_ptr<Material> material,
			int vertexPerFace,
			std::string associatedTextureName,
			int stride,
			int elementsPerRowOfCombinedData,
			int vertexSize, int vertexOffset, gl::GLenum vertexType,
			int normalSize, int normalOffset, gl::GLenum normalType,
			int colourSize, int colourOffset, gl::GLenum colourType,
			int textureCoordSize, int textureCoordOffset, gl::GLenum textureCoordType,
			std::vector<float> combinedData
        );
	///
	/// This calculates every time.
	/// \return an AABB that bounds the entire Model. If for some reason there is no vertex data the bounding box will simply be the origin.
	///
	AABB getAABB();
};
