#ifndef TERRAIN_DATA_H
#define TERRAIN_DATA_H

#include <memory>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "utils/colour.h"
#include "graphics/terrainpolygon.h"

///
/// Contains the data required to reconstruct the terrain of a world. Currently, this is
/// a collection of TerrainPolygon and some metadata including the total number of vertices
/// of all the polygons and the total number of elements (vertices, normals, colours, texture-coords)
/// to describe the entire terrain.
///
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
	///
	/// Constructs a new TerrainData object with the specified initial values.
	///
	TerrainData(std::vector<glm::vec3> verts, std::vector<glm::vec3> normals, std::vector<Colour> colours, std::vector<glm::vec2> textureCoords,
		std::vector<glm::vec3> faceVerts, std::vector<glm::vec3> faceNormals, std::vector<glm::vec3> faceTextures);
	TerrainData();
	///
	/// Gets the array of TerrainPolygons in this TerrainData.
	///
	std::shared_ptr<FlexArray<TerrainPolygon>> getPolygons();
	///
	/// The total number of vertices of all the polygons in the TerrainData. It is expected that this value
	/// should be in the interval [0, INF]
	///
    int getTotalNumberOfVertices();
	void exportToOBJ(std::string filePath);
};

#endif
