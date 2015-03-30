#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include <string>
#include <memory>
#include <glbinding/gl/gl.h>
#include "physics/aabb.h"
#include "utils/flexarray.h"
#include "world/material.h"

/**
 * Contains data to create a VBO to draw a model. That is, vertex data, normals, colour, and texture coordinates.
 */
class MeshData
{
public:
	const std::string associatedTextureName;
	const gl::GLenum glRenderMode;
	const int stride;
	const int vertexSize;
	const int vertexOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const gl::GLenum vertexType;
	const int normalSize;
	const int normalOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const gl::GLenum normalType;
	const int colourSize;
	const int colourOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const gl::GLenum colourType;
	const int textureCoordSize;
	const int textureCoordOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const gl::GLenum textureCoordType;
	/** The total number of elements associated to one vertex*/
	const int elementsPerRowOfCombinedData;
	FlexArray<float> combinedData;
	const int vertexPerFace;
	bool hasTextureData;
    std::shared_ptr<Material> material;

	/**
	 * Builds a new ModelData and disables textures.
	 * @param glRenderMode
	 * @param vertexPerFace
	 * @param associatedTextureName
	 * @param stride
	 * @param elementsPerRowOfCombinedData
	 * @param vertexSize
	 * @param vertexOffset
	 * @param vertexType
	 * @param normalSize
	 * @param normalOffset
	 * @param normalType
	 * @param colourSize
	 * @param colourOffset
	 * @param colourType
	 * @param combinedData
	 */
	MeshData(
			gl::GLenum glRenderMode,
			int vertexPerFace,
			int stride,
			int elementsPerRowOfCombinedData,
			int vertexSize, int vertexOffset, gl::GLenum vertexType,
			int normalSize, int normalOffset, gl::GLenum normalType,
			int colourSize, int colourOffset, gl::GLenum colourType,
			FlexArray<float> combinedData
        );
	/**
	 * Builds a new ModelData and enables textures
	 * @param hasTextureData
	 * @param glRenderMode
	 * @param vertexPerFace
	 * @param associatedTextureName
	 * @param stride
	 * @param elementsPerRowOfCombinedData
	 * @param vertexSize
	 * @param vertexOffset
	 * @param vertexType
	 * @param normalSize
	 * @param normalOffset
	 * @param normalType
	 * @param colourSize
	 * @param colourOffset
	 * @param colourType
	 * @param textureCoordSize
	 * @param textureCoordOffset
	 * @param textureCoordType
	 * @param combinedData
	 */
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
			FlexArray<float> combinedData
        );
	/**
	 * This calculates every time.
	 * @return an AABB that bounds the entire Model. If for some reason there is no vertex
	 * data the bounding box will simply be the origin.
	 */
	AABB getAABB();
};

#endif
