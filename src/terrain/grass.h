#ifndef ENG_GRASS_GEN_H
#define ENG_GRASS_GEN_H

#include <memory>
#include <glm/vec3.hpp>
#include "graphics/camera.h"
#include "render/vbo.h"
#include "render/texture.h"
#include "shaders/shader.h"

class Grass
{
public:
    Grass(int density, glm::vec3 center, glm::vec3 randomizationOffsets, float range, std::shared_ptr<Texture> texture);
    void update();
    void draw(Camera *camera);
private:
    std::shared_ptr<Texture> texture;
    int density;
    std::shared_ptr<VBO> vbo;
    glm::vec3 windDirection;
    float maxTimeOfCurrentBurst;
    float remainingTime;
    float timeUntilNextBurst;
    unsigned long long previousTime;
    unsigned long long deltaTime;
    std::shared_ptr<Shader> grassShader;
    float maxWindPower;
	glm::vec3 randomizationOffsets;
    float getWindPower();
    void generateNewWind();
    void createVBO(glm::vec3 center, float range);
};




#endif
