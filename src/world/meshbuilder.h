#ifndef MODEL_DATA_BUILDER_H
#define MODEL_DATA_BUILDER_H

#include <memory>
#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glbinding/gl/gl.h>
#include "utils/colour.h"
#include "render/vbo.h"
#include "world/meshdata.h"

std::shared_ptr<MeshData> createModelDataFromParsedOBJ(gl::GLenum glRenderMode,
        std::shared_ptr<Material> material,
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
        FlexArray<glm::vec3> faceTextures);

MeshData createModelData(gl::GLenum glRenderMode,
        int vertexPerFace,
        std::string associatedTextureName,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        int textureCoordSize, gl::GLenum textureCoordType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData,
        FlexArray<float> textureCoordData);

MeshData createModelDataNoTexture(gl::GLenum glRenderMode,
        int vertexPerFace,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
        FlexArray<float> vertexData,
        FlexArray<float> normalData,
        FlexArray<float> colourData);

MeshData getDerpyDefaultData();

#endif
