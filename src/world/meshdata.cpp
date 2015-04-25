#include "world/meshdata.h"

MeshData::MeshData(
        gl::GLenum glRenderMode,
        int vertexPerFace,
        int stride,
        int elementsPerRowOfCombinedData,
        int vertexSize, int vertexOffset, gl::GLenum vertexType,
        int normalSize, int normalOffset, gl::GLenum normalType,
        int colourSize, int colourOffset, gl::GLenum colourType,
		std::vector<float> combinedData
    ) : associatedTextureName(""), glRenderMode(glRenderMode), stride(stride),
    vertexSize(vertexSize), vertexOffset(vertexOffset), vertexType(vertexType),
    normalSize(normalSize), normalOffset(normalOffset), normalType(normalType),
    colourSize(colourSize), colourOffset(colourOffset), colourType(colourType),
    textureCoordSize(0), textureCoordOffset(0), textureCoordType(gl::GL_FLOAT),
    elementsPerRowOfCombinedData(elementsPerRowOfCombinedData), combinedData(combinedData),
    vertexPerFace(vertexPerFace), hasTextureData(false)
{
}

MeshData::MeshData(
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
    ) : associatedTextureName(associatedTextureName), glRenderMode(glRenderMode), stride(stride),
    vertexSize(vertexSize), vertexOffset(vertexOffset), vertexType(vertexType),
    normalSize(normalSize), normalOffset(normalOffset), normalType(normalType),
    colourSize(colourSize), colourOffset(colourOffset), colourType(colourType),
    textureCoordSize(textureCoordSize), textureCoordOffset(textureCoordOffset), textureCoordType(textureCoordType),
    elementsPerRowOfCombinedData(elementsPerRowOfCombinedData), combinedData(combinedData),
    vertexPerFace(vertexPerFace), hasTextureData(false), material(material)
{
}

AABB MeshData::getAABB()
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
    int polyCount = static_cast<int>(combinedData.size()) / elementsPerRowOfCombinedData;

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


