
#include <memory>
#include <sstream>
#include <glbinding/gl/gl.h>
#include "objparser.h"
#include "world/meshbuilder.h"
#include "utils/colour.h"
#include "utils/fileutils.h"
#include "utils/misc.h"

ObjParser::ObjParser(std::string fileName, std::string textureName) : fileName(fileName), textureName(textureName), modelName("")
{
    loadData();
}

std::shared_ptr<Model> ObjParser::exportModel()
{
    return std::shared_ptr<Model>(new Model(meshes));
}
/*
std::shared_ptr<TerrainData> ObjParser::exportTerrain()
{
    for(glm::vec3 data : vertices)
    {
        colours.push_back(Colour(0, 1, 0, 1));
    }
    return std::shared_ptr<TerrainData>(new TerrainData(vertices, normals, colours, textureCoords, faceVerts, faceNormals, faceTextures));
}
*/
void ObjParser::loadData()
{
    using namespace gl;
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

    for(unsigned int i = 0; i < fileContents.size(); i++)
    {
        line = fileContents[i];
        std::vector<std::string> splitLine = split(line, ' ');
        if (line.find("o ") == 0) // startsWith
        {
            if(hasEncounteredMesh)
            {
                std::shared_ptr<MeshData> data = createModelDataFromParsedOBJ(
                    GL_TRIANGLES,
                    meshName,
                    3, GL_FLOAT,
                    GL_FLOAT,
                    4,	GL_FLOAT,
                    2, GL_FLOAT,
                    make1DFlex(vertices),
                    make1DFlex(faceVerts),
                    make1DFlex(normals, vertices.size()),
                    make1DFlex(faceNormals),
                    FlexArray<Colour>(),
                    make1DFlex(textureCoords),
                    make1DFlex(faceTextures)
                );
                meshes.push_back(data);
              //  vertices = std::vector<glm::vec3>();
              //  normals = std::vector<glm::vec3>();
              //  colours = std::vector<Colour>();
                //textureCoords = std::vector<glm::vec2>();
                faceVerts = std::vector<glm::vec3>();
                faceNormals = std::vector<glm::vec3>();
                faceTextures = std::vector<glm::vec3>();
            }
            hasEncounteredMesh = true;
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
    }
    std::shared_ptr<MeshData> data = createModelDataFromParsedOBJ(
        GL_TRIANGLES,
        meshName,
        3, GL_FLOAT,
        GL_FLOAT,
        4,	GL_FLOAT,
        2, GL_FLOAT,
        make1DFlex(vertices),
        make1DFlex(faceVerts),
        make1DFlex(normals, vertices.size()),
        make1DFlex(faceNormals),
        FlexArray<Colour>(),
        make1DFlex(textureCoords),
        make1DFlex(faceTextures)
    );
    meshes.push_back(data);
    std::cout << "Num Meshes:" << meshes.size() << std::endl;
}

