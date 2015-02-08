#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include <string>
#include "physics/aabb.h"
#include "utils/flexarray.h"

/**
 * Contains data to create a VBO to draw a model. That is, vertex data, normals, colour, and texture coordinates.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class ModelData
{
public:
	const std::string associatedTextureName;
	const int glRenderMode;
	const int stride;
	const int vertexSize;
	const int vertexOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const int vertexType;
	const int normalSize;
	const int normalOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const int normalType;
	const int colourSize;
	const int colourOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const int colourType;
	const int textureCoordSize;
	const int textureCoordOffset;
	/** Corresponds to a GL constant type like GL11.GL_FLOAT, or GL11.GL_BYTE*/
	const int textureCoordType;
	/** The total number of elements associated to one vertex*/
	const int elementsPerRowOfCombinedData;
	FlexArray<float> combinedData;
	const int vertexPerFace;
	bool hasTextureData;

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
	ModelData(
			int glRenderMode,
			int vertexPerFace,
			int stride,
			int elementsPerRowOfCombinedData,
			int vertexSize, int vertexOffset, int vertexType,
			int normalSize, int normalOffset, int normalType,
			int colourSize, int colourOffset, int colourType,
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
	ModelData(
			int glRenderMode,
			int vertexPerFace,
			std::string associatedTextureName,
			int stride,
			int elementsPerRowOfCombinedData,
			int vertexSize, int vertexOffset, int vertexType,
			int normalSize, int normalOffset, int normalType,
			int colourSize, int colourOffset, int colourType,
			int textureCoordSize, int textureCoordOffset, int textureCoordType,
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
