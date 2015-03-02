
#include <glm/vec3.hpp>
#include "utils/flexarray.h"
#include "terrainrenderer.h"


TerrainPolygon p(
        FlexArray<glm::vec3>({
                glm::vec3(3.0f,  1.0f, -1.0f),
                glm::vec3(3.0f,  1.0f,  1.0f),
                glm::vec3(3.0f, -1.0f,  1.0f),
                glm::vec3(3.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon p1(
        FlexArray<glm::vec3>({
                glm::vec3(5.0f,  1.0f, -1.0f),
                glm::vec3(5.0f,  1.0f,  1.0f),
                glm::vec3(5.0f, -1.0f,  1.0f),
                glm::vec3(5.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,0.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon p2(
        FlexArray<glm::vec3>({
                glm::vec3(7.0f,  1.0f, -1.0f),
                glm::vec3(7.0f,  1.0f,  1.0f),
                glm::vec3(7.0f, -1.0f,  1.0f),
                glm::vec3(7.0f, -1.0f, -1.0f)
        }),
        FlexArray<float>({
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);
TerrainPolygon p3(
        FlexArray<glm::vec3> {
                glm::vec3(10.0f,  1.0f, -1.0f),
                glm::vec3(10.0f,  1.0f,  1.0f),
                glm::vec3(10.0f, -1.0f,  1.0f),
                glm::vec3(10.0f, -1.0f, -1.0f)
        },
        FlexArray<float>({
                0.0f,0.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f,
                0.0f,1.0f,1.0f,1.0f
        }),
        FlexArray<float>({
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                1.0f, 0.0f
        })
);

TerrainRenderer::TerrainRenderer() : terrainPolygons(FlexArray<TerrainPolygon>(100)), vbo(new DynamicVBO())
{
}

void TerrainRenderer::create(std::shared_ptr<TerrainData> terrain, std::shared_ptr<Texture> terrainTexture)
{
    std::shared_ptr<FlexArray<TerrainPolygon>> polys = terrain->getPolygons();
    vbo->create(polys, terrainTexture);
}

void TerrainRenderer::draw(Camera *cam)
{
    vbo->draw(cam);
}

TerrainRenderer::~TerrainRenderer()
{
    delete vbo;
}
