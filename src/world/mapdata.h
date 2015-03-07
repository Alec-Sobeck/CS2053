#ifndef MAP_DATA_H
#define MAP_DATA_H

#include <vector>
#include "world/meshdata.h"
#include "terrain/terraindata.h"

/**
 * MapData is the save format for an entire map, containing data on the terrain
 * and the models.
 * @author Alec Sobeck
 * @author Matthew Robertson
 */
class MapData
{
public:
	std::vector<MeshData> completeModelDataList;
	TerrainData data;
	/**
	 * Constructs a new MapData and stores references to the List<ModelData> and TerrainData provided.
	 * @param initialModels a List<ModelData> that should describe the entirety of the models in this MapData
	 * @param data a TerrainData object that should describe the entirely of the terrain of this MapData
	 */
	MapData(std::vector<MeshData> initialModels, TerrainData data);
};




#endif
