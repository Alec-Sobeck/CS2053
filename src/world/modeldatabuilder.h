#ifndef MODEL_DATA_BUILDER_H
#define MODEL_DATA_BUILDER_H

#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "utils/colour.h"
#include "render/vbo.h"
#include "world/modeldata.h"

ModelData createModelDataFromParsedOBJ(int glRenderMode,
        std::string associatedTextureName,
        int vertexSize, int vertexType,
        int normalType,
        int colourSize, int colourType,
        int textureCoordSize, int textureCoordType,
        FlexArray<glm::vec3> vertexData,
        FlexArray<glm::vec3> faceVerts,
        FlexArray<glm::vec3> normalData,
        FlexArray<glm::vec3> faceNormals,
        FlexArray<Colour> colourData,
        FlexArray<glm::vec2> textureData,
        FlexArray<glm::vec3> faceTextures);

ModelData createModelData(int glRenderMode,
        int vertexPerFace,
        std::string associatedTextureName,
        int vertexSize, int vertexType,
        int normalType,
        int colourSize, int colourType,
        int textureCoordSize, int textureCoordType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData,
        FlexArray<float> textureCoordData);

ModelData createModelDataNoTexture(int glRenderMode,
        int vertexPerFace,
        int vertexSize, int vertexType,
        int normalType,
        int colourSize, int colourType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData);

ModelData getDerpyDefaultData();



#endif
