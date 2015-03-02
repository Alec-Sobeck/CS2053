
#include "world/map.h"

Map::Map() : models(std::vector<Model>()), data(std::shared_ptr<TerrainData>(new TerrainData())),
        terrainOctree(nullptr), modelOctree(nullptr)
{
    //TODO fix the issue where no octree bounds can be defined immediately
//		terrainOctree = new Octree<TerrainPolygon>(absoluteMapBoundary, new ArrayList<TerrainPolygon>(), 0);
//		modelOctree = new Octree<Model>(absoluteMapBoundary, new ArrayList<Model>(), 0);
}

Map::~Map()
{
    if(terrainOctree)
    {
        delete terrainOctree;
    }
    if(modelOctree)
    {
        delete modelOctree;
    }
}

/**
 * Constructs a new Map with an empty ArrayList of Models, an empty ArrayList
 * of terrain Polygons, and an Octree empty for the models and terrain.
 * @param absoluteMapBoundary the AABB that bounds the entire map-
 */
Map::Map(AABB absoluteMapBoundary) : models(std::vector<Model>()),
        data(std::shared_ptr<TerrainData>(new TerrainData()))
{
    terrainOctree = new Octree<TerrainPolygon>(absoluteMapBoundary, std::vector<TerrainPolygon>(), 0);
    modelOctree = new Octree<Model>(absoluteMapBoundary, std::vector<Model>(), 0);
}

/**
 * Adds a Model to this Map. This includes adding it to the modelOctree
 * @param model a Model to add to this Map
 */
void Map::addModel(Model &model)
{
    models.push_back(model);
    modelOctree->insertElement(model);
}

void Map::setTerrain(std::shared_ptr<TerrainData> terrainData)
{
    this->data = terrainData;
    std::shared_ptr<FlexArray<TerrainPolygon>> polys = terrainData->getPolygons();
    for (unsigned int i = 0; i < polys->size(); i++)
    {
        this->terrainOctree->insertElement(polys->at(i));
    }
}

std::shared_ptr<TerrainData> Map::getData()
{
    return data;
}
