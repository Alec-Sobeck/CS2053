#ifndef MAP_DATA_H
#define MAP_DATA_H

#include <vector>
#include "world/meshdata.h"
#include "terrain/terraindata.h"

///
/// MapData is the save format for an entire map, containing data on the terrain and the models.
///
class MapData
{
public:
	std::vector<MeshData> completeModelDataList;
	TerrainData data;
	///
	/// Constructs a new MapData and stores references to the ModelData and TerrainData provided.
	///
	MapData(std::vector<MeshData> initialModels, TerrainData data);
};




#endif
