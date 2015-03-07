
#include "world/mapdata.h"

MapData::MapData(std::vector<MeshData> initialModels, TerrainData data)
    : completeModelDataList(initialModels), data(data)
{
}
