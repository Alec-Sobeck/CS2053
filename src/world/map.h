#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <memory>
#include <vector>
#include "physics/aabb.h"
#include "math/octree.h"
#include "graphics/model.h"
#include "terrain/terraindata.h"

/**
 * Map implements all the basic yet important features to handle the 3D world. This includes managing the models
 * and terrain data. Rendering functionality is not provided in Map, although the data to do collision detections is
 * found within Map
 * @author Alec Sobeck
 */
class Map
{
private:

public:
	const std::string FILE_EXTENSION = ".mapdat";
    std::vector<Model> models;
	std::shared_ptr<TerrainData> data;
	Octree<TerrainPolygon> *terrainOctree;
	Octree<Model> *modelOctree;
	Map();
	/**
	 * Constructs a new Map with an empty ArrayList of Models, an empty ArrayList
	 * of terrain Polygons, and an Octree empty for the models and terrain.
	 * @param absoluteMapBoundary the AABB that bounds the entire map-
	 */
	Map(AABB absoluteMapBoundary);
	~Map();
	/**
	 * Adds a Model to this Map. This includes adding it to the modelOctree
	 * @param model a Model to add to this Map
	 */
	void addModel(Model &model);
	void setTerrain(std::shared_ptr<TerrainData>);
	std::shared_ptr<TerrainData> getData();
};

#endif
