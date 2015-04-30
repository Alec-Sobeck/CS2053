#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glbinding/gl/gl.h>
#include "utils/colour.h"
#include "render/vbo.h"
#include "world/meshdata.h"
#include "world/vaomeshdata.h"

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
		std::vector<glm::vec3> faceTextures);

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
);

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
		std::vector<float> textureCoordData);

MeshData createModelDataNoTexture(gl::GLenum glRenderMode,
        int vertexPerFace,
        int vertexSize, gl::GLenum vertexType,
        gl::GLenum normalType,
        int colourSize, gl::GLenum colourType,
		std::vector<float> vertexData,
		std::vector<float> normalData,
		std::vector<float> colourData);

