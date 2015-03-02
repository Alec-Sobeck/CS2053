#include "modeldatabuilder.h"

#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "utils/colour.h"
#include "render/vbo.h"
#include "world/modeldata.h"

ModelData createModelDataFromParsedOBJ(gl::GLenum glRenderMode,
        std::string associatedTextureName,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        int textureCoordSize, gl::GLenum textureCoordType,
        FlexArray<glm::vec3> vertexData,
        FlexArray<glm::vec3> faceVerts,
        FlexArray<glm::vec3> normalData,
        FlexArray<glm::vec3> faceNormals,
        FlexArray<Colour> colourData,
        FlexArray<glm::vec2> textureData,
        FlexArray<glm::vec3> faceTextures)
{
    using namespace gl;
    const int vertsPerFace = 3;

    //This is a brutal check to prevent possible bugs. Things might work for these render modes,
    //but because they havent been tested it's not worth the risk.
    if (glRenderMode == GL_POINTS || glRenderMode == GL_LINES || glRenderMode == GL_LINE_STRIP ||
        glRenderMode == GL_LINE_LOOP || glRenderMode == GL_POLYGON)
    {
//            GL_POINTS
//            GL_LINES
//            GL_LINE_STRIP
//            GL_LINE_LOOP
//            GL_TRIANGLES
//            GL_TRIANGLE_STRIP
//            GL_TRIANGLE_FAN
//            GL_QUADS
//            GL_QUAD_STRIP
//            GL_POLYGON
        throw std::invalid_argument("Illegal glRenderMode parameter provided. Only GL_TRIANGLE, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, QL_QUADS, and GL_QUAD_STRIP are supported. ");
    }

    int runningOffset = 0;
    //Vertex stuff
    int vertexOffset = runningOffset;
    runningOffset += vertexSize * sizeof(vertexType);
    //Normal stuff
    int normalSize = 3;
    int normalOffset = runningOffset;
    runningOffset += normalSize * sizeof(normalType);
    //Colour stuff
    int colourOffset = runningOffset;
    runningOffset += colourSize * sizeof(colourType);
    int textureCoordOffset = runningOffset;
    int elementsPerRowOfCombinedData = vertexSize + normalSize + colourSize + textureCoordSize;
    //TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    //Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType) +
            textureCoordSize * sizeof(textureCoordType);

    FlexArray<float> combinedBuffer(faceVerts.size() * vertsPerFace * elementsPerRowOfCombinedData);
    int k = 0;

    for (int i = 0; i < faceVerts.size(); i++)
    {
        glm::vec3 facesVerts = faceVerts[i];
        glm::vec3 facesNormals = faceNormals[i];
        glm::vec3 facesTextures = faceTextures[i];
        // X
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.x - 1)].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.x - 1)].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.x - 1)].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.x - 1)].x);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.x - 1)].y);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.x - 1)].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.x - 1].r);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.x - 1].g);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.x - 1].b);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.x - 1].a);
        // Add in UV textureData
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.x - 1)].x);
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.x - 1)].y);

        //Y
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.y - 1)].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.y - 1)].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.y - 1)].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.y - 1)].x);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.y - 1)].y);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.y - 1)].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.y - 1].r);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.y - 1].g);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.y - 1].b);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.y - 1].a);
        // Add in UV textureData
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.y - 1)].x);
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.y - 1)].y);

        //Z
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.z - 1)].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.z - 1)].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[static_cast<int>(facesVerts.z - 1)].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.z - 1)].x);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.z - 1)].y);
        combinedBuffer[k++] = static_cast<float>(normalData[static_cast<int>(facesNormals.z - 1)].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.z - 1].r);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.z - 1].g);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.z - 1].b);
        combinedBuffer[k++] = static_cast<float>(colourData[facesVerts.z - 1].a);
        // Add in UV textureData
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.z - 1)].x);
        combinedBuffer[k++] = static_cast<float>(textureData[static_cast<int>(facesTextures.z - 1)].y);
    }

    return ModelData(glRenderMode, vertsPerFace,
            associatedTextureName,
            stride,
            elementsPerRowOfCombinedData,
            vertexSize, vertexOffset, vertexType,
            normalSize, normalOffset, normalType,
            colourSize, colourOffset, colourType,
            textureCoordSize, textureCoordOffset, textureCoordType,
            combinedBuffer);

}

ModelData createModelData(gl::GLenum glRenderMode,
        int vertexPerFace,
        std::string associatedTextureName,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        int textureCoordSize, gl::GLenum textureCoordType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData,
        FlexArray<float> textureCoordData)
{
    using namespace gl;
    //This is a brutal check to prevent possible bugs. Things might work for these render modes,
    //but because they havent been tested it's not worth the risk.
    if (glRenderMode == GL_POINTS || glRenderMode == GL_LINES || glRenderMode == GL_LINE_STRIP ||
        glRenderMode == GL_LINE_LOOP || glRenderMode == GL_POLYGON)
    {
//            GL_POINTS
//            GL_LINES
//            GL_LINE_STRIP
//            GL_LINE_LOOP
//            GL_TRIANGLES
//            GL_TRIANGLE_STRIP
//            GL_TRIANGLE_FAN
//            GL_QUADS
//            GL_QUAD_STRIP
//            GL_POLYGON
        throw std::invalid_argument("Illegal glRenderMode parameter provided. Only GL_TRIANGLE, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, QL_QUADS, and GL_QUAD_STRIP are supported. ");
    }

    int runningOffset = 0;
    //Vertex stuff
    int vertexOffset = runningOffset;
    runningOffset += vertexSize * sizeof(vertexType);
    //Normal stuff
    int normalSize = 3;
    int normalOffset = runningOffset;
    runningOffset += normalSize * sizeof(normalType);
    //Colour stuff
    int colourOffset = runningOffset;
    runningOffset += colourSize * sizeof(colourType);
    //Texture stuff
    int textureCoordOffset = runningOffset;
    int elementsPerRowOfCombinedData = normalSize + vertexSize + colourSize + textureCoordSize;
    //TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    //Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType) +
            textureCoordSize * sizeof(textureCoordType);

    FlexArray<float> combinedBuffer(vertexData.size() + normalData.size() + colourData.size() + textureCoordData.size());
    for(int i = 0; i < combinedBuffer.size() / elementsPerRowOfCombinedData; i++)
    {
        int j = 0;
        for(int k = 0; k < vertexSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = vertexData[(i * vertexSize) + k];
            j++;
        }
        for(int k = 0; k < normalSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = normalData[(i * normalSize) + k];
            j++;
        }
        for(int k = 0; k < colourSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = colourData[i * colourSize + k];
            j++;
        }
        for(int k = 0; k < textureCoordSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = textureCoordData[i * textureCoordSize + k];
            j++;
        }
    }

    return ModelData(glRenderMode, vertexPerFace, associatedTextureName, stride, elementsPerRowOfCombinedData,
            vertexSize, vertexOffset, vertexType, normalSize, normalOffset, normalType, colourSize, colourOffset,
            colourType, textureCoordSize, textureCoordOffset, textureCoordType, combinedBuffer);
}

ModelData createModelDataNoTexture(gl::GLenum glRenderMode,
        int vertexPerFace,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData)
{
    using namespace gl;
    //This is a brutal check to prevent possible bugs. Things might work for these render modes,
    //but because they havent been tested it's not worth the risk.
    if (glRenderMode == GL_POINTS || glRenderMode == GL_LINES || glRenderMode == GL_LINE_STRIP ||
        glRenderMode == GL_LINE_LOOP || glRenderMode == GL_POLYGON)
    {
//            GL_POINTS
//            GL_LINES
//            GL_LINE_STRIP
//            GL_LINE_LOOP
//            GL_TRIANGLES
//            GL_TRIANGLE_STRIP
//            GL_TRIANGLE_FAN
//            GL_QUADS
//            GL_QUAD_STRIP
//            GL_POLYGON
        throw std::invalid_argument("Illegal glRenderMode parameter provided. Only GL_TRIANGLE, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, QL_QUADS, and GL_QUAD_STRIP are supported. ");
    }

    int runningOffset = 0;
    //Vertex stuff
    int vertexOffset = runningOffset;
    runningOffset += vertexSize * sizeof(vertexType);
    //Normal stuff
    int normalSize = 3;
    int normalOffset = runningOffset;
    runningOffset += normalSize * sizeof(normalType);
    //Colour stuff
    int colourOffset = runningOffset;
    runningOffset += colourSize * sizeof(colourType);
    //Texture stuff
    int elementsPerRowOfCombinedData = normalSize + vertexSize + colourSize;
    //TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    //Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType);

    FlexArray<float> combinedBuffer(vertexData.size() + normalData.size() + colourData.size());
    for(int i = 0; i < combinedBuffer.size() / elementsPerRowOfCombinedData; i++)
    {
        int j = 0;
        for(int k = 0; k < vertexSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = vertexData[(i * vertexSize) + k];
            j++;
        }
        for(int k = 0; k < normalSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = normalData[(i * normalSize) + k];
            j++;
        }
        for(int k = 0; k < colourSize; k++)
        {
            combinedBuffer[(i * elementsPerRowOfCombinedData) + j] = colourData[i * colourSize + k];
            j++;
        }

    }

    return ModelData(glRenderMode,
            vertexPerFace,
            stride,
            elementsPerRowOfCombinedData,
            vertexSize,
            vertexOffset,
            vertexType,
            normalSize,
            normalOffset,
            normalType,
            colourSize,
            colourOffset,
            colourType,
            combinedBuffer);
}

/**
 * Test function
 */
ModelData getDerpyDefaultData()
{
    using namespace gl;
    FlexArray<float> vertexData = {
        //   x      y      z
        // back quad
             0.0f, -1.0f, 2.0f,
             2.0f, -1.0f, 2.0f,
             2.0f, 5.0f,  2.0f,
             0.0f, 5.0f,  2.0f,
        // front quad
             0.0f, -1.0f, 0.0f,
             0.0f, 5.0f, 0.0f,
             2.0f, 5.0f,  0.0f,
             2.0f, -1.0f,  0.0f,
        // left quad
            0.0f, -1.0f, 2.0f,
            0.0f, 5.0f, 2.0f,
            0.0f,  5.0f, 0.0f,
            0.0f,  -1.0f, 0.0f,
        // right quad
             2.0f, -1.0f, 2.0f,
             2.0f, -1.0f, 0.0f,
             2.0f, 5.0f,  0.0f,
             2.0f, 5.0f,  2.0f,
         // top quad
             0.0f,  5.0f, 0.0f,
             0.0f,  5.0f, 2.0f,
             2.0f,  5.0f, 2.0f,
             2.0f,  5.0f, 0.0f,
         // bottom quad
             0.0f, -1.0f, 0.0f,
             2.0f, -1.0f, 0.0f,
             2.0f, -1.0f, 2.0f,
             0.0f, -1.0f, 2.0f,
        };

    FlexArray<float> normalData = {
        //  nx     ny     nz
        // back quad
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,
             0.0f,  0.0f,  1.0f,

        // front quad
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,
             0.0f,  0.0f, -1.0f,

        // left quad
             -1.0f,  0.0f,  0.0f,
             -1.0f,  0.0f,  0.0f,
             -1.0f,  0.0f,  0.0f,
             -1.0f,  0.0f,  0.0f,

        // right quad
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,
             1.0f,  0.0f,  0.0f,

        // top quad
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,
             0.0f,  1.0f,  0.0f,

        // bottom quad
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
             0.0f, -1.0f,  0.0f,
        };

    FlexArray<float> colourData = {
        //   r      g      b      a
        // back quad

            1.0f,  0.0f,  0.0f,  1.0f,
            1.0f,  0.0f,  0.0f,  1.0f,
            1.0f,  0.0f,  0.0f,  1.0f,
            1.0f,  0.0f,  0.0f,  1.0f,

        // front quad
            0.0f,  1.0f,  0.0f,  1.0f,
            0.0f,  1.0f,  0.0f,  1.0f,
            0.0f,  1.0f,  0.0f,  1.0f,
            0.0f,  1.0f,  0.0f,  1.0f,

        // left quad
            0.0f,  0.0f,  1.0f,  1.0f,
            0.0f,  0.0f,  1.0f,  1.0f,
            0.0f,  0.0f,  1.0f,  1.0f,
            0.0f,  0.0f,  1.0f,  1.0f,

        // right quad
            1.0f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.0f,  1.0f,  1.0f,

        // top quad
            1.0f,  1.0f,  0.0f,  1.0f,
            1.0f,  1.0f,  0.0f,  1.0f,
            1.0f,  1.0f,  0.0f,  1.0f,
            1.0f,  1.0f,  0.0f,  1.0f,

        // bottom quad
            0.0f,  1.0f,  1.0f,  1.0f,
            0.0f,  1.0f,  1.0f,  1.0f,
            0.0f,  1.0f,  1.0f,  1.0f,
            0.0f,  1.0f,  1.0f,  1.0f
        };



   FlexArray<float> textureCoordData = {
        //  u		v
        // back quad
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

        // front quad
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

        // left quad
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

        // right quad
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

        // top quad
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

        // bottom quad
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
        };
//			return ModelDataBuilder.createModelData(GL_QUADS,
//	 				4,
//	 				Render.sun.getAssociatedFileName(),
//	 				3, GL_FLOAT, GL_FLOAT, 4, GL_FLOAT, 2, GL_FLOAT,
//	 				vertexData,
//	 				normalData,
//	 				colourData,
//	 				textureCoordData
//	 				);
//
    return createModelDataNoTexture(
        GL_QUADS,
        4,
        3, GL_FLOAT, GL_FLOAT, 4, GL_FLOAT,
        vertexData,
        normalData,
        colourData
    );
}


