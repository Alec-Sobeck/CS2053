#ifndef TERRAIN_DATA_H
#define TERRAIN_DATA_H

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "utils/colour.h"
#include "terrainpolygon.h"

/**
 * Contains the data required to reconstruct the terrain of a world. Currently, this is
 * a collection of TerrainPolygon and some metadata including the total number of vertices
 * of all the polygons and the total number of elements (vertices, normals, colours, texture-coords)
 * to describe the entire terrain.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class TerrainData
{
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> faceVerts;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec3> faceTextures;
	bool statsNeedRecalculated;

public:
	/**
	 * Constructs a new TerrainData object with the specified initial values.
	 */
	TerrainData(std::vector<glm::vec3> verts, std::vector<glm::vec3> normals, std::vector<Colour> colours, std::vector<glm::vec2> textureCoords,
		std::vector<glm::vec3> faceVerts, std::vector<glm::vec3> faceNormals, std::vector<glm::vec3> faceTextures);
	TerrainData();
	/**
	 * Gets the List of TerrainPolygons in this TerrainData.
	 * @return a List<TerrainPolygon> that belong to this TerrainData
	 */
	std::vector<TerrainPolygon> getPolygons();
	/**
	 * The total number of vertices of all the polygons in the TerrainData. It is expected that this value
	 * should be in the interval [0, INF]
	 * @return
	 */
    int getTotalNumberOfVertices();
	void exportToOBJ(std::string filePath);
};

#endif
