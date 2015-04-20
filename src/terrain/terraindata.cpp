
#include <sstream>
#include "terraindata.h"
#include "utils/fileutils.h"

TerrainData::TerrainData(std::vector<glm::vec3> verts,
                         std::vector<glm::vec3> normals,
                         std::vector<Colour> colours,
                         std::vector<glm::vec2> textureCoords,
                         std::vector<glm::vec3> faceVerts,
                         std::vector<glm::vec3> faceNormals,
                         std::vector<glm::vec3> faceTextures)
    : vertices(verts), normals(normals), colours(colours), textureCoords(textureCoords), faceVerts(faceVerts),
        faceNormals(faceNormals), faceTextures(faceTextures)
{
}

TerrainData::TerrainData() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), colours(std::vector<Colour>()),
                             textureCoords(std::vector<glm::vec2>()), faceVerts(std::vector<glm::vec3>()), faceNormals(std::vector<glm::vec3>()),
                             faceTextures(std::vector<glm::vec3>())
{
}

std::shared_ptr<std::vector<TerrainPolygon>> TerrainData::getPolygons()
{
	std::shared_ptr<std::vector<TerrainPolygon>> polygons(new std::vector<TerrainPolygon>(faceVerts.size()));

    for (int i = 0; i < static_cast<int>(faceVerts.size()); i++)
    {
        glm::vec3 faceVertVals = faceVerts.at(i);
        glm::vec3 faceUVVals = faceTextures.at(i);

		std::vector<glm::vec3> polyVerts(3);
		std::vector<float> polyColours(12);
		std::vector<float> polyUVs(6);

        // x
        polyVerts[0] = vertices.at(static_cast<int>(faceVertVals.x - 1));
        polyColours[0] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.x - 1)).r);
        polyColours[1] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.x - 1)).g);
        polyColours[2] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.x - 1)).b);
        polyColours[3] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.x - 1)).a);
        polyUVs[0] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.x - 1)).x);
        polyUVs[1] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.x - 1)).y);

        // y
        polyVerts[1] = vertices.at(static_cast<int>(faceVertVals.y - 1));
        polyColours[4] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.y - 1)).r);
        polyColours[5] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.y - 1)).g);
        polyColours[6] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.y - 1)).b);
        polyColours[7] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.y - 1)).a);
        polyUVs[2] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.y - 1)).x);
        polyUVs[3] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.y - 1)).y);

        // z
        polyVerts[2] = vertices.at(static_cast<int>(faceVertVals.z - 1));
        polyColours[8] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.z - 1)).r);
        polyColours[9] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.z - 1)).g);
        polyColours[10] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.z - 1)).b);
        polyColours[11] = static_cast<float>(colours.at(static_cast<int>(faceVertVals.z - 1)).a);
        polyUVs[4] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.z - 1)).x);
        polyUVs[5] = static_cast<float>(textureCoords.at(static_cast<int>(faceUVVals.z - 1)).y);

        TerrainPolygon poly(polyVerts, polyColours, polyUVs);
        (*polygons)[i] = poly;
    }

    return polygons;
}

int TerrainData::getTotalNumberOfVertices()
{
    return vertices.size();
}

void TerrainData::exportToOBJ(std::string filePath)
{
    std::stringstream ss;
    std::string filepath = filePath + ".obj";

    for (glm::vec3 vertex : vertices)
    {
        ss << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    for (glm::vec3 normal : normals)
    {
        ss << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
    }

    glm::vec3 *faceVert = nullptr;
    glm::vec3 *faceNormal = nullptr;
    glm::vec3 *faceTexture = nullptr;

    for (int i = 0; i < static_cast<int>(faceVerts.size()); i++)
    {
        ss << "f ";
        faceVert = &faceVerts.at(i);
        if (faceNormals.size() >= faceVerts.size())
        {
            faceNormal = &faceNormals.at(i);
        }
        else
        {
            faceNormal = nullptr;
        }

        if (faceTextures.size() >= faceVerts.size())
        {
            faceTexture = &faceTextures.at(i);
        }
        else
        {
            faceTexture = nullptr;
        }

        // x
        ss << faceVert->x;
        if (faceTexture != nullptr)
        {
            ss << "/" << static_cast<int>(faceTexture->x);
            if (faceNormal != nullptr)
            {
                ss << "/" << static_cast<int>(faceNormal->x);
            }
        }
        else if (faceNormal != nullptr)
        {
            ss << "//" << static_cast<int>(faceNormal->x);
        }
        ss << " ";
        // end x

        // y
        ss << faceVert->y;
        if (faceTexture != nullptr)
        {
            ss << "/" << static_cast<int>(faceTexture->y);
            if (faceNormal != nullptr)
            {
                ss << "/" << static_cast<int>(faceNormal->y);
            }
        }
        else if (faceNormal != nullptr)
        {
            ss << "//" << static_cast<int>(faceNormal->y);
        }
        ss << " ";
        // end y

        // z
        ss << faceVert->z;
        if (faceTexture != nullptr)
        {
            ss << "/" << static_cast<int>(faceTexture->z);
            if (faceNormal != nullptr)
            {
                ss << "/" << static_cast<int>(faceNormal->z);
            }
        }
        else if (faceNormal != nullptr)
        {
            ss << "//" << static_cast<int>(faceNormal->z);
        }
        ss << " ";
        // end z

        ss << "\n";
    }

    writeTextFile(filepath, ss.str());
}
