
#include "world/mapdata.h"

MapData::MapData(std::vector<ModelData> initialModels, TerrainData data)
    : completeModelDataList(initialModels), data(data)
{
}
