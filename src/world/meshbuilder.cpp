#include "meshbuilder.h"

#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "utils/colour.h"
#include "render/vbo.h"
#include "world/meshdata.h"

inline int fmodp(int num, int mod)
{
/*
    num = num % mod;
    while(num < 0)
    {
        num += mod;
    }
    return num;
*/
    return (num >= 0) ? num : (num + mod == -1) ? 0 : mod + num;
}

std::shared_ptr<VAOMeshData> createVAOMeshFromParsedOBJ(
	gl::GLenum glRenderMode,
	std::shared_ptr<Material> material,
	std::string associatedTextureName,
	int vertexSize, gl::GLenum vertexType,
	gl::GLenum normalType,
	int colourSize, gl::GLenum colourType,
	int textureCoordSize, gl::GLenum textureCoordType,
	std::vector<glm::vec3> vertexData,
	std::vector<glm::vec3> faceVerts,
	std::vector<glm::vec3> normalData,
	std::vector<glm::vec3> faceNormals,
	std::vector<Colour> colourData,
	std::vector<glm::vec2> textureData,
	std::vector<glm::vec3> faceTextures
	)
{
	using namespace gl;
	int numVerts = faceVerts.size() * 3;
	float* vertices = new float[numVerts * 3];
	float* colours = new float[numVerts * 4];
	float* normals = new float[numVerts * 3];
	float* textures = new float[numVerts * 2];
	
	// Fill in a bunch of default data if none is provided.
	if (faceNormals.size() == 0)
	{
		normalData = std::vector<glm::vec3>(vertexData.size());
		for (int i = 0; i < normalData.size(); i++)
		{
			normalData[i] = glm::vec3(1, 0, 0);
		}
		faceNormals = std::vector<glm::vec3>(faceVerts.size());
		for (int i = 0; i < faceNormals.size(); i++)
		{
			faceNormals[i] = glm::vec3(5, 5, 5);
		}
	}
	if (colourData.size() == 0)
	{
		colourData = std::vector<Colour>(vertexData.size());
		for (int i = 0; i < colourData.size(); i++)
		{
			colourData[i] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	int v = 0;
	int c = 0;
	int n = 0;
	int t = 0;

	for (int i = 0; i < faceVerts.size(); i++)
	{
		glm::vec3 facesVerts = faceVerts[i];
		glm::vec3 facesNormals = faceNormals[i];
		glm::vec3 facesTextures = faceTextures[i];
		// X
		// Stuff the vert data
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].x);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].y);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].z);
		// Then add associated normal
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].x);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].y);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].z);
		//Then add associated vert colour
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1), colourData.size())].r);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1), colourData.size())].g);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1), colourData.size())].b);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1), colourData.size())].a);
		// Add in UV textureData
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.x - 1), textureData.size())].x);
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.x - 1), textureData.size())].y);

		//Y
		// Stuff the vert data
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].x);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].y);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].z);
		// Then add associated normal
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].x);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].y);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].z);
		//Then add associated vert colour
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y - 1), colourData.size())].r);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y - 1), colourData.size())].g);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y - 1), colourData.size())].b);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y - 1), colourData.size())].a);
		// Add in UV textureData
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.y - 1), textureData.size())].x);
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.y - 1), textureData.size())].y);

		//Z
		// Stuff the vert data
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].x);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].y);
		vertices[v++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].z);
		// Then add associated normal
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].x);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].y);
		normals[n++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].z);
		//Then add associated vert colour
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z - 1), colourData.size())].r);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z - 1), colourData.size())].g);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z - 1), colourData.size())].b);
		colours[c++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z - 1), colourData.size())].a);
		// Add in UV textureData
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.z - 1), textureData.size())].x);
		textures[t++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.z - 1), textureData.size())].y);
	}


	return std::shared_ptr<VAOMeshData>(new VAOMeshData(
		numVerts,
		vertices,
		numVerts * 3 * sizeof(float),
		
		normals,
		numVerts * 3 * sizeof(float),
		colours,
		numVerts * 4 * sizeof(float),
		textures, 
		numVerts * 2 * sizeof(float),
		glRenderMode,
		material
	));
}


std::shared_ptr<MeshData> createModelDataFromParsedOBJ(gl::GLenum glRenderMode,
        std::shared_ptr<Material> material,
        std::string associatedTextureName,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        int textureCoordSize, gl::GLenum textureCoordType,
		std::vector<glm::vec3> vertexData,
		std::vector<glm::vec3> faceVerts,
		std::vector<glm::vec3> normalData,
		std::vector<glm::vec3> faceNormals,
		std::vector<Colour> colourData,
		std::vector<glm::vec2> textureData,
		std::vector<glm::vec3> faceTextures)
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

    if(faceNormals.size() == 0)
    {
		normalData = std::vector<glm::vec3>(vertexData.size());
        for(int i = 0; i < normalData.size(); i++)
        {
            normalData[i] = glm::vec3(1, 0, 0);
        }
		faceNormals = std::vector<glm::vec3>(faceVerts.size());
        for(int i = 0; i < faceNormals.size(); i++)
        {
            faceNormals[i] = glm::vec3(5, 5, 5);
        }
    }

    if(colourData.size() == 0)
    {
		colourData = std::vector<Colour>(vertexData.size());
        for(int i = 0; i < colourData.size(); i++)
        {
            colourData[i] = Colour(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
    int textureCoordOffset = runningOffset;
    int elementsPerRowOfCombinedData = vertexSize + normalSize + colourSize + textureCoordSize;
    // @TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    // Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType) +
            textureCoordSize * sizeof(textureCoordType);

	std::vector<float> combinedBuffer(faceVerts.size() * vertsPerFace * elementsPerRowOfCombinedData);
    int k = 0;

    for (int i = 0; i < faceVerts.size(); i++)
    {
        glm::vec3 facesVerts = faceVerts[i];
        glm::vec3 facesNormals = faceNormals[i];
        glm::vec3 facesTextures = faceTextures[i];
        // X
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.x - 1), vertexData.size())].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].x);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].y);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.x - 1), normalData.size())].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1) ,colourData.size())].r);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1) ,colourData.size())].g);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1) ,colourData.size())].b);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.x - 1) ,colourData.size())].a);
        // Add in UV textureData

        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.x - 1),textureData.size())].x);
        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.x - 1),textureData.size())].y);

        //Y
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.y - 1), vertexData.size())].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].x);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].y);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.y - 1), normalData.size())].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y- 1) ,colourData.size())].r);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y- 1) ,colourData.size())].g);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y- 1) ,colourData.size())].b);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.y- 1) ,colourData.size())].a);
        // Add in UV textureData
        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.y - 1),textureData.size())].x);
        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.y - 1),textureData.size())].y);

        //Z
        // Stuff the vert data
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].x);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].y);
        combinedBuffer[k++] = static_cast<float>(vertexData[fmodp(static_cast<int>(facesVerts.z - 1), vertexData.size())].z);
        // Then add associated normal
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].x);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].y);
        combinedBuffer[k++] = static_cast<float>(normalData[fmodp(static_cast<int>(facesNormals.z - 1), normalData.size())].z);
        //Then add associated vert colour
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z- 1) ,colourData.size())].r);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z- 1) ,colourData.size())].g);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z- 1) ,colourData.size())].b);
        combinedBuffer[k++] = static_cast<float>(colourData[fmodp(static_cast<int>(facesVerts.z- 1) ,colourData.size())].a);
        // Add in UV textureData
        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.z - 1),textureData.size())].x);
        combinedBuffer[k++] = static_cast<float>(textureData[fmodp(static_cast<int>(facesTextures.z - 1),textureData.size())].y);
    }

    return std::shared_ptr<MeshData>(new MeshData(glRenderMode, material, vertsPerFace,
            associatedTextureName,
            stride,
            elementsPerRowOfCombinedData,
            vertexSize, vertexOffset, vertexType,
            normalSize, normalOffset, normalType,
            colourSize, colourOffset, colourType,
            textureCoordSize, textureCoordOffset, textureCoordType,
            combinedBuffer));

}

MeshData createModelData(gl::GLenum glRenderMode,
        int vertexPerFace,
        std::string associatedTextureName,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        int textureCoordSize, gl::GLenum textureCoordType,
		std::vector<float> vertexData,
		std::vector<float> normalData,
		std::vector<float> colourData,
		std::vector<float> textureCoordData)
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
    // @TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    // Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType) +
            textureCoordSize * sizeof(textureCoordType);

	std::vector<float> combinedBuffer(vertexData.size() + normalData.size() + colourData.size() + textureCoordData.size());
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

    return MeshData(glRenderMode, std::shared_ptr<Material>(nullptr), vertexPerFace, associatedTextureName, stride, elementsPerRowOfCombinedData,
            vertexSize, vertexOffset, vertexType, normalSize, normalOffset, normalType, colourSize, colourOffset,
            colourType, textureCoordSize, textureCoordOffset, textureCoordType, combinedBuffer);
}

MeshData createModelDataNoTexture(gl::GLenum glRenderMode,
        int vertexPerFace,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
		std::vector<float> vertexData,
		std::vector<float> normalData,
		std::vector<float> colourData)
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
    // @TODO determine if something besides a float[] is required to make sure that different data types dont cause bugs
    //Find how large the data is
    int stride = vertexSize * sizeof(vertexType) +
            normalSize * sizeof(normalType) +
            colourSize * sizeof(colourType);

	std::vector<float> combinedBuffer(vertexData.size() + normalData.size() + colourData.size());
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

    return MeshData(glRenderMode,
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

