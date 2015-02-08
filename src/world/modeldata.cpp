#include "world/modeldata.h"

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
ModelData::ModelData(
        int glRenderMode,
        int vertexPerFace,
        int stride,
        int elementsPerRowOfCombinedData,
        int vertexSize, int vertexOffset, int vertexType,
        int normalSize, int normalOffset, int normalType,
        int colourSize, int colourOffset, int colourType,
        FlexArray<float> combinedData
    ) : associatedTextureName(""), glRenderMode(glRenderMode), stride(stride),
    vertexSize(vertexSize), vertexOffset(vertexOffset), vertexType(vertexType),
    normalSize(normalSize), normalOffset(normalOffset), normalType(normalType),
    colourSize(colourSize), colourOffset(colourOffset), colourType(colourType),
    textureCoordSize(0), textureCoordOffset(0), textureCoordType(0),
    elementsPerRowOfCombinedData(elementsPerRowOfCombinedData), combinedData(combinedData),
    vertexPerFace(vertexPerFace), hasTextureData(false)
{
}

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
ModelData::ModelData(
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
    ) : associatedTextureName(associatedTextureName), glRenderMode(glRenderMode), stride(stride),
    vertexSize(vertexSize), vertexOffset(vertexOffset), vertexType(vertexType),
    normalSize(normalSize), normalOffset(normalOffset), normalType(normalType),
    colourSize(colourSize), colourOffset(colourOffset), colourType(colourType),
    textureCoordSize(textureCoordSize), textureCoordOffset(textureCoordOffset), textureCoordType(textureCoordType),
    elementsPerRowOfCombinedData(elementsPerRowOfCombinedData), combinedData(combinedData),
    vertexPerFace(vertexPerFace), hasTextureData(false)
{
}

/**
 * This calculates every time.
 * @return an AABB that bounds the entire Model. If for some reason there is no vertex
 * data the bounding box will simply be the origin.
 */
AABB ModelData::getAABB()
{
    if(combinedData.size() == 0)
    {
        return AABB(0, 0, 0, 0, 0, 0);
    }
    float xMin = combinedData[0];
    float xMax = combinedData[0];
    float yMin = combinedData[1];
    float yMax = combinedData[1];
    float zMin = combinedData[2];
    float zMax = combinedData[2];
    int polyCount = combinedData.size() / elementsPerRowOfCombinedData;

    //xMin
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 0] < xMin)
        {
            xMin = combinedData[i * elementsPerRowOfCombinedData + 0];
        }
    }
    //xMax
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 0] > xMax)
        {
            xMax = combinedData[i * elementsPerRowOfCombinedData + 0];
        }
    }
    //yMin
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 1] < yMin)
        {
            yMin = combinedData[i * elementsPerRowOfCombinedData + 1];
        }
    }
    //yMax
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 1] > yMax)
        {
            yMax = combinedData[i * elementsPerRowOfCombinedData + 1];
        }
    }
    //zMin
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 2] < zMin)
        {
            zMin = combinedData[i * elementsPerRowOfCombinedData + 2];
        }
    }
    //zMax
    for(int i = 0; i < polyCount; i++)
    {
        if(combinedData[i * elementsPerRowOfCombinedData + 2] > zMax)
        {
            zMax = combinedData[i * elementsPerRowOfCombinedData + 2];
        }
    }

    return AABB(xMin, yMin, zMin, xMax, yMax, zMax);
}


