
#include <memory>
#include <sstream>
#include <glbinding/gl/gl.h>
#include "objparser.h"
#include "world/meshbuilder.h"
#include "utils/colour.h"
#include "utils/fileutils.h"
#include "utils/misc.h"
#include "utils/materialparser.h"

ObjParser::ObjParser(std::string filePath, std::string fileName, std::string textureName, bool dataIsTriangles) 
	: filePath(filePath), fileName(fileName), textureName(textureName), modelName("")
{
    loadData(dataIsTriangles);
}

std::shared_ptr<Model> ObjParser::exportModel()
{
    return std::shared_ptr<Model>(new Model(meshes));
}

void ObjParser::loadData(bool dataIsTriangles)
{
    using namespace gl;
    GLenum renderMode = (dataIsTriangles) ? GL_TRIANGLES : GL_QUADS;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;
    std::vector<std::string> fileContents = readTextFileAsLines(fileName);
    std::string line;
    bool hasEncounteredMesh = false;
    std::string meshName = "";
    std::shared_ptr<Material> activeMaterial(nullptr);

    for(unsigned int i = 0; i < fileContents.size(); i++)
    {
        line = fileContents[i];
        std::vector<std::string> splitLine = split(line, ' ');
        if (line.find("o ") == 0 || line.find("g ") == 0) // startsWith
        {
            if(hasEncounteredMesh)
            {
				normals.resize(vertices.size());
                std::shared_ptr<MeshData> data = createModelDataFromParsedOBJ(
                    renderMode,
                    activeMaterial,
                    meshName,
                    3, GL_FLOAT,
                    GL_FLOAT,
                    4,	GL_FLOAT,
                    2, GL_FLOAT,
                    vertices,
                    faceVerts,
                    normals,
                    faceNormals,
					std::vector<Colour>(),
                    textureCoords,
                    faceTextures
                );
                meshes.push_back(data);
                faceVerts = std::vector<glm::vec3>();
                faceNormals = std::vector<glm::vec3>();
                faceTextures = std::vector<glm::vec3>();
            }
            hasEncounteredMesh = true;
            std::cout << "MeshName: >" << splitLine.at(1) << "<" << std::endl;
            meshName = splitLine.at(1);
        }
        else if (line.find("v ") == 0)
        {
            vertices.push_back(glm::vec3(parseDouble(splitLine.at(1)),
                                    parseDouble(splitLine.at(2)),
                                    parseDouble(splitLine.at(3))));
        }
        else if (line.find("vn ") == 0)
        {
            normals.push_back(glm::vec3(parseDouble(splitLine.at(1)),
                    parseDouble(splitLine.at(2)),
                    parseDouble(splitLine.at(3))));
        }
        else if (line.find("vt ") == 0)
        {
            textureCoords.push_back(
                glm::vec2(
                    parseDouble(splitLine.at(1)),
                    parseDouble(splitLine.at(2))
                )
            );
        }
        else if (line.find("f ") == 0)
        {
            if(dataIsTriangles)
            {
                std::vector<std::string> firstVert = split(splitLine.at(1), '/');
                std::vector<std::string> secondVert = split(splitLine.at(2), '/');
                std::vector<std::string> thirdVert = split(splitLine.at(3), '/');
                faceVerts.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(0))),
                        static_cast<int>(parseDouble(secondVert.at(0))),
                        static_cast<int>(parseDouble(thirdVert.at(0)))));
                faceTextures.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(1))),
                        static_cast<int>(parseDouble(secondVert.at(1))),

                        static_cast<int>(parseDouble(thirdVert.at(1)))));
                if (firstVert.size() > 2)
                {
                    faceNormals.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(2))),
                            static_cast<int>(parseDouble(secondVert.at(2))),
                            static_cast<int>(parseDouble(thirdVert.at(2)))));
                }
            }
            else /// Assumption: this must indicate quads because the graphics hardware doesn't really support anything else.
            {
                /// If the data is a quad, break it into 2 separate triangles.
                std::vector<std::string> firstVert = split(splitLine.at(1), '/');
                std::vector<std::string> secondVert = split(splitLine.at(2), '/');
                std::vector<std::string> thirdVert = split(splitLine.at(3), '/');
                std::vector<std::string> fourthVert = split(splitLine.at(4), '/');
                /// Make the first triangle
                faceVerts.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(0))),
                        static_cast<int>(parseDouble(secondVert.at(0))),
                        static_cast<int>(parseDouble(fourthVert.at(0)))));
                faceTextures.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(1))),
                        static_cast<int>(parseDouble(secondVert.at(1))),

                        static_cast<int>(parseDouble(fourthVert.at(1)))));
                if (firstVert.size() > 2)
                {
                    faceNormals.push_back(glm::vec3(static_cast<int>(parseDouble(firstVert.at(2))),
                            static_cast<int>(parseDouble(secondVert.at(2))),
                            static_cast<int>(parseDouble(fourthVert.at(2)))));
                }
                /// Make the second triangle
                faceVerts.push_back(glm::vec3(static_cast<int>(parseDouble(secondVert.at(0))),
                        static_cast<int>(parseDouble(thirdVert.at(0))),
                        static_cast<int>(parseDouble(fourthVert.at(0)))));
                faceTextures.push_back(glm::vec3(static_cast<int>(parseDouble(secondVert.at(1))),
                        static_cast<int>(parseDouble(thirdVert.at(1))),

                        static_cast<int>(parseDouble(fourthVert.at(1)))));
                if (firstVert.size() > 2)
                {
                    faceNormals.push_back(glm::vec3(static_cast<int>(parseDouble(secondVert.at(2))),
                            static_cast<int>(parseDouble(thirdVert.at(2))),
                            static_cast<int>(parseDouble(fourthVert.at(2)))));
                }
            }
        }
        else if(line.find("mtllib ") == 0)
        {
            std::string filename = splitLine.at(1);
            if(filename.find("./") == 0)
            {
                filename = filename.substr(2);
            }
            std::stringstream ss;
            ss << filePath << filename;
            std::vector<std::string> fileContents = readTextFileAsLines(ss.str());
            MaterialParser matParser(fileContents);
            std::map<std::string, std::shared_ptr<Material>> mats = matParser.parseMaterials();
            std::cout << "Read: " << mats.size() << " materials" << std::endl;
            for(const auto &myPair : mats)
            {
                materials[myPair.first] = myPair.second;
            }
        }
        else if(line.find("usemtl ") == 0)
        {
            activeMaterial = materials[splitLine.at(1)];
        }
    }
	
	normals.resize(vertices.size());
    std::shared_ptr<MeshData> data = createModelDataFromParsedOBJ(
        renderMode,
        activeMaterial,
        meshName,
        3, GL_FLOAT,
        GL_FLOAT,
        4,	GL_FLOAT,
        2, GL_FLOAT,
        vertices,
        faceVerts,
        normals,
        faceNormals,
		std::vector<Colour>(),
        textureCoords,
        faceTextures
    );
    meshes.push_back(data);

    std::cout << "Num Meshes:" << meshes.size() << std::endl;
}

