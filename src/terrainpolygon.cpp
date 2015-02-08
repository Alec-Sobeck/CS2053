
#include "terrainpolygon.h"


TerrainPolygon::TerrainPolygon(std::vector<glm::vec3> vertices, FlexArray<float> colour, FlexArray<float> textureCoords)
 : Polygon3(vertices), polygonBounds(generateBounds()), colour(colour), textureCoords(textureCoords)
{
}

FlexArray<float> TerrainPolygon::getRawData()
{
    float nx = normal.x;
    float ny = normal.y;
    float nz = normal.z;
    FlexArray<float> combinedData(points.size() * (TOTAL_ROW_SIZE));
    for(int i = 0; i < static_cast<int>(points.size()); i++)
    {
        combinedData[(i * TOTAL_ROW_SIZE) + 0] = points[i].x;
        combinedData[(i * TOTAL_ROW_SIZE) + 1] = points[i].y;
        combinedData[(i * TOTAL_ROW_SIZE) + 2] = points[i].z;
        combinedData[(i * TOTAL_ROW_SIZE) + 3] = nx;
        combinedData[(i * TOTAL_ROW_SIZE) + 4] = ny;
        combinedData[(i * TOTAL_ROW_SIZE) + 5] = nz;
        combinedData[(i * TOTAL_ROW_SIZE) + 6] = colour[i * 4];
        combinedData[(i * TOTAL_ROW_SIZE) + 7] = colour[i * 4 + 1];
        combinedData[(i * TOTAL_ROW_SIZE) + 8] = colour[i * 4 + 2];
        combinedData[(i * TOTAL_ROW_SIZE) + 9] = colour[i * 4 + 3];
        combinedData[(i * TOTAL_ROW_SIZE) + 10] = textureCoords[i * 2];
        combinedData[(i * TOTAL_ROW_SIZE) + 11] = textureCoords[i * 2 + 1];
    }
    return combinedData;
}

AABB TerrainPolygon::getAABB()
{
    return polygonBounds;
}

void TerrainPolygon::onAABBCollision(AABB &a)
{
}

FlexArray<int> TerrainPolygon::getIBOIndexes()
{
    return IBOIndexes;
}

void TerrainPolygon::setIBOIndexes(FlexArray<int> &iBOIndexes)
{
    this->IBOIndexes = iBOIndexes;
}

FlexArray<float> TerrainPolygon::getTextureCoords()
{
    return textureCoords;
}

FlexArray<float> TerrainPolygon::getColour()
{
    return colour;
}

/**
 * Approximates the bounds of the Polygon3 associated to this TerrainPolygon.
 * This bounding box will still work even if one of the lengths of the sides
 * is exactly equal to zero.
 * @return
 */
AABB TerrainPolygon::generateBounds()
{
    double xMin = points[0].x;
    double xMax = points[0].x;
    double yMin = points[1].y;
    double yMax = points[1].y;
    double zMin = points[2].z;
    double zMax = points[2].z;
    for(int i = 1; i < static_cast<int>(points.size()); i++)
    {
        //xMin
        if(points[i].x < xMin)
        {
            xMin = points[i].x;
        }
        //xMax
        if(points[i].x > xMax)
        {
            xMax = points[i].x;
        }
        //yMin
        if(points[i].y < yMin)
        {
            yMin = points[i].y;
        }
        //yMax
        if(points[i].y > yMax)
        {
            yMax = points[i].y;
        }
        //zMin
        if(points[i].z < zMin)
        {
            zMin = points[i].z;
        }
        //zMax
        if(points[i].z > zMax)
        {
            zMax = points[i].z;
        }
    }
    return AABB(xMin, yMin, zMin, xMax, yMax, zMax);
}







