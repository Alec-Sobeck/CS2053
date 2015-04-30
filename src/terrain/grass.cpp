#include <vld.h>
#include <cmath>
#include <vector>
#include "math/gamemath.h"
#include "terrain/grass.h"
#include "utils/random.h"
#include "utils/timehelper.h"
#include "utils/fileutils.h"
#include "graphics/gluhelper.h"
#include "world/vaomeshdata.h"
#include "graphics/terrainpolygon.h"


Grass::Grass(int density, glm::vec3 center, glm::vec3 randomizationOffsets, float range, std::shared_ptr<Texture> texture) : texture(texture), density(density), 
	vao(nullptr),
    windDirection(glm::vec3(0, 0, 0)), maxTimeOfCurrentBurst(0), remainingTime(0), timeUntilNextBurst(0), previousTime(getCurrentTimeMillis()), deltaTime(0),
	grassShader(std::shared_ptr<Shader>(nullptr)), maxWindPower(0), randomizationOffsets(randomizationOffsets)
{
    seedRandomGenerator();
    createVBO(center, range);
}

void Grass::update()
{
    unsigned long long previousUpdateTime = previousTime;
    unsigned long long currentTime = getCurrentTimeMillis();
    this->deltaTime = currentTime - previousUpdateTime;
    this->remainingTime -= static_cast<float>(deltaTime) / 1000.0f;
    this->timeUntilNextBurst -= static_cast<float>(deltaTime) / 1000.0f;
    if(this->timeUntilNextBurst <= 0)
    {
        generateNewWind();
    }
    this->previousTime = currentTime;
}

void Grass::generateNewWind()
{
    maxTimeOfCurrentBurst = getRandomFloat() * 7.0f + 3.6f;
    remainingTime = maxTimeOfCurrentBurst;
    timeUntilNextBurst = maxTimeOfCurrentBurst + (getRandomFloat() * 4.66f) + 2.4f;
    float randomAngle = getRandomFloat() * 2 * PI;
    windDirection = glm::vec3(cos(randomAngle), 0, sin(randomAngle));
    maxWindPower = 0.3f + (getRandomFloat() * 0.5f);
}

void Grass::draw(GLState &glState, Camera *camera)
{
    using namespace gl;
    glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glState.loadIdentity();

    float power = getWindPower();
    grassShader->bindShader();

	grassShader->glUniform1("texture1", 0);
	grassShader->glUniformMatrix4("modelMatrix", gl::GL_FALSE, glState.model);
	grassShader->glUniformMatrix4("projMatrix", gl::GL_FALSE, glState.proj);
	grassShader->glUniformMatrix4("viewMatrix", gl::GL_FALSE, glState.view);

    grassShader->glUniform3("windDirection", windDirection);
    grassShader->glUniform1("windPower", power);
    vao->draw();

	glEnable(GL_CULL_FACE);
}

inline void putGrassCluster(float *vertices, float *normals, float *colours, float *textures, int index, glm::vec3 o/*offset*/)
{
	float xHalfSize = 0.3f;
	float yHalfSize = 0.3f;
	float zHalfSize = 0.3f;
	float xMinus = -xHalfSize;
	float xPlus = xHalfSize;
	float yMinus = 0.0f;
	float yPlus = 2.0f * yHalfSize;
	float zMinus = -zHalfSize;
	float zPlus = zHalfSize;

    float sin30 = sin(rad(30.0f));
    float cos30 = cos(rad(30.0f));
	/// --------------------------------------------------------
    /// Vert #1 -- triangle 1
    // Verts
    vertices[index * 54 + 0 * 0 + 0] = o.x + 0.0f;
	vertices[index * 54 + 0 * 0 + 1] = o.y + yMinus;
	vertices[index * 54 + 0 * 0 + 2] = o.z + zPlus;
    // Normals
	normals[index * 54 + 0 * 0 + 0] = 1.0f;
	normals[index * 54 + 0 * 0 + 1] = 0.0f;
	normals[index * 54 + 0 * 0 + 2] = 0.0f;
    // Colour
	colours[index * 72 + 0 * 0 + 0] = 1.0f;
	colours[index * 72 + 0 * 0 + 1] = 1.0f;
	colours[index * 72 + 0 * 0 + 2] = 1.0f;
	colours[index * 72 + 0 * 0 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 0 * 0 + 0] = 1.0f;
	textures[index * 36 + 0 * 0 + 1] = 0.0f;
    /// Vert #2 -- triangle 1 
    // Verts
	vertices[index * 54 + 1 * 3 + 0] = o.x + 0.0f;
	vertices[index * 54 + 1 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 1 * 3 + 2] = o.z + zPlus;
    // Normals
	normals[index * 54 + 1 * 3 + 0] = 1.0f;
	normals[index * 54 + 1 * 3 + 1] = 0.0f;
	normals[index * 54 + 1 * 3 + 2] = 0.0f;
    // Colour
	colours[index * 72 + 1 * 4 + 0] = 0.0f;
	colours[index * 72 + 1 * 4 + 1] = 0.0f;
	colours[index * 72 + 1 * 4 + 2] = 0.0f;
	colours[index * 72 + 1 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 1 * 2 + 0] = 1.0f;
	textures[index * 36 + 1 * 2 + 1] = 1.0f;
    /// Vert #3 -- triangle 1
    // Verts
	vertices[index * 54 + 2 * 3 + 0] = o.x + 0.0f;
	vertices[index * 54 + 2 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 2 * 3 + 2] = o.z + zMinus;
    // Normals
	normals[index * 54 + 2 * 3 + 0] = 1.0f;
	normals[index * 54 + 2 * 3 + 1] = 0.0f;
	normals[index * 54 + 2 * 3 + 2] = 0.0f;
    // Colour
	colours[index * 72 + 2 * 4 + 0] = 0.0f;
	colours[index * 72 + 2 * 4 + 1] = 0.0f;
	colours[index * 72 + 2 * 4 + 2] = 0.0f;
	colours[index * 72 + 2 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 2 * 2 + 0] = 0.0f;
	textures[index * 36 + 2 * 2 + 1] = 1.0f;
	/// --------------------------------------------------------
	/// Vert #1 -- triangle 2
	// Verts
	vertices[index * 54 + 3 * 3 + 0] = o.x + 0.0f;
	vertices[index * 54 + 3 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 3 * 3 + 2] = o.z + zMinus;
	// Normals
	normals[index * 54 + 3 * 3 + 0] = 1.0f;
	normals[index * 54 + 3 * 3 + 1] = 0.0f;
	normals[index * 54 + 3 * 3 + 2] = 0.0f;
	// Colour
	colours[index * 72 + 3 * 4 + 0] = 0.0f;
	colours[index * 72 + 3 * 4 + 1] = 0.0f;
	colours[index * 72 + 3 * 4 + 2] = 0.0f;
	colours[index * 72 + 3 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 3 * 2 + 0] = 0.0f;
	textures[index * 36 + 3 * 2 + 1] = 1.0f;
    /// Vert #2 -- triangle 2
    // Verts
	vertices[index * 54 + 4 * 3 + 0] = o.x + 0.0f;
	vertices[index * 54 + 4 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 4 * 3 + 2] = o.z + zMinus;
    // Normals
	normals[index * 54 + 4 * 3 + 0] = 1.0f;
	normals[index * 54 + 4 * 3 + 1] = 0.0f;
	normals[index * 54 + 4 * 3 + 2] = 0.0f;
    // Colour
	colours[index * 72 + 4 * 4 + 0] = 1.0f;
	colours[index * 72 + 4 * 4 + 1] = 1.0f;
	colours[index * 72 + 4 * 4 + 2] = 1.0f;
	colours[index * 72 + 4 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 4 * 2 + 0] = 0.0f;
	textures[index * 36 + 4 * 2 + 1] = 0.0f;
	/// Vert #3 -- triangle 2
	// Verts
	vertices[index * 54 + 5 * 3 + 0] = o.x + 0.0f;
	vertices[index * 54 + 5 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 5 * 3 + 2] = o.z + zPlus;
	// Normals
	normals[index * 54 + 5 * 3 + 0] = 1.0f;
	normals[index * 54 + 5 * 3 + 1] = 0.0f;
	normals[index * 54 + 5 * 3 + 2] = 0.0f;
	// Colour
	colours[index * 72 + 5 * 4 + 0] = 1.0f;
	colours[index * 72 + 5 * 4 + 1] = 1.0f;
	colours[index * 72 + 5 * 4 + 2] = 1.0f;
	colours[index * 72 + 5 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 5 * 2 + 0] = 1.0f;
	textures[index * 36 + 5 * 2 + 1] = 0.0f;
	/// --------------------------------------------------------
///
/// Quad 2
///
    /// Vert #1 -- triangle 3
    // Verts
	vertices[index * 54 + 6 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 6 * 3 + 1] = o.y + 0.0f;
	vertices[index * 54 + 6 * 3 + 2] = o.z + sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 6 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 6 * 3 + 1] = yMinus;
	normals[index * 54 + 6 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 6 * 4 + 0] = 1.0f;
	colours[index * 72 + 6 * 4 + 1] = 1.0f;
	colours[index * 72 + 6 * 4 + 2] = 1.0f;
	colours[index * 72 + 6 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 6 * 2 + 0] = 1.0f;
	textures[index * 36 + 6 * 2 + 1] = 0.0f;
    /// Vert #2 -- triangle 3
    // Verts
	vertices[index * 54 + 7 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 7 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 7 * 3 + 2] = o.z + sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 7 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 7 * 3 + 1] = 0.0f;
	normals[index * 54 + 7 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 7 * 4 + 0] = 0.0f;
	colours[index * 72 + 7 * 4 + 1] = 0.0f;
	colours[index * 72 + 7 * 4 + 2] = 0.0f;
	colours[index * 72 + 7 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 7 * 2 + 0] = 1.0f;
	textures[index * 36 + 7 * 2 + 1] = 1.0f;
    /// Vert #3 -- triangle 3
    // Verts
	vertices[index * 54 + 8 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 8 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 8 * 3 + 2] = o.z + -sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 8 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 8 * 3 + 1] = 0.0f;
	normals[index * 54 + 8 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 8 * 4 + 0] = 0.0f;
	colours[index * 72 + 8 * 4 + 1] = 0.0f;
	colours[index * 72 + 8 * 4 + 2] = 0.0f;
	colours[index * 72 + 8 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 8 * 2 + 0] = 0.0f;
	textures[index * 36 + 8 * 2 + 1] = 1.0f;
	/// --------------------------------------------------------
    /// Vertex #1 -- triangle 4
	// Verts
	vertices[index * 54 + 9 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 9 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 9 * 3 + 2] = o.z + -sin30 * zHalfSize;
	// Normals
	normals[index * 54 + 9 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 9 * 3 + 1] = 0.0f;
	normals[index * 54 + 9 * 3 + 2] = 1.732f / 1.999956f;
	// Colour
	colours[index * 72 + 9 * 4 + 0] = 0.0f;
	colours[index * 72 + 9 * 4 + 1] = 0.0f;
	colours[index * 72 + 9 * 4 + 2] = 0.0f;
	colours[index * 72 + 9 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 9 * 2 + 0] = 0.0f;
	textures[index * 36 + 9 * 2 + 1] = 1.0f;
	/// Vertex #2 -- triangle 4
	// Verts
	vertices[index * 54 + 10 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 10 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 10 * 3 + 2] = o.z + -sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 10 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 10 * 3 + 1] = 0.0f;
	normals[index * 54 + 10 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 10 * 4 + 0] = 1.0f;
	colours[index * 72 + 10 * 4 + 1] = 1.0f;
	colours[index * 72 + 10 * 4 + 2] = 1.0f;
	colours[index * 72 + 10 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 10 * 2 + 0] = 0.0f;
	textures[index * 36 + 10 * 2 + 1] = 0.0f;
	/// Vertex #3 -- triangle 4
	// Verts
	vertices[index * 54 + 11 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 11 * 3 + 1] = o.y + 0.0f;
	vertices[index * 54 + 11 * 3 + 2] = o.z + sin30 * zHalfSize;
	// Normals
	normals[index * 54 + 11 * 3 + 0] = -1.0f / 1.999956f;
	normals[index * 54 + 11 * 3 + 1] = yMinus;
	normals[index * 54 + 11 * 3 + 2] = 1.732f / 1.999956f;
	// Colour
	colours[index * 72 + 11 * 4 + 0] = 1.0f;
	colours[index * 72 + 11 * 4 + 1] = 1.0f;
	colours[index * 72 + 11 * 4 + 2] = 1.0f;
	colours[index * 72 + 11 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 11 * 2 + 0] = 1.0f;
	textures[index * 36 + 11 * 2 + 1] = 0.0f;
	/// --------------------------------------------------------
///
/// Quad 3
///
    /// Vert #1 -- triangle 5
    // Verts
	vertices[index * 54 + 12 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 12 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 12 * 3 + 2] = o.z + -sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 12 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 12 * 3 + 1] = 0.0f;
	normals[index * 54 + 12 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 12 * 4 + 0] = 1.0f;
	colours[index * 72 + 12 * 4 + 1] = 1.0f;
	colours[index * 72 + 12 * 4 + 2] = 1.0f;
	colours[index * 72 + 12 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 12 * 2 + 0] = 1.0f;
	textures[index * 36 + 12 * 2 + 1] = 0.0f;
    /// Vert #2 -- triangle 5
    // Verts
	vertices[index * 54 + 13 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 13 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 13 * 3 + 2] = o.z + -sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 13 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 13 * 3 + 1] = 0.0f;
	normals[index * 54 + 13 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 13 * 4 + 0] = 0.0f;
	colours[index * 72 + 13 * 4 + 1] = 0.0f;
	colours[index * 72 + 13 * 4 + 2] = 0.0f;
	colours[index * 72 + 13 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 13 * 2 + 0] = 1.0f;
	textures[index * 36 + 13 * 2 + 1] = 1.0f;
    /// Vert #3 -- triangle 5
    // Verts
	vertices[index * 54 + 14 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 14 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 14 * 3 + 2] = o.z + sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 14 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 14 * 3 + 1] = 0.0f;
	normals[index * 54 + 14 * 3 + 2] = 1.732f / 1.999956f;
    // Colour
	colours[index * 72 + 14 * 4 + 0] = 0.0f;
	colours[index * 72 + 14 * 4 + 1] = 0.0f;
	colours[index * 72 + 14 * 4 + 2] = 0.0f;
	colours[index * 72 + 14 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 14 * 2 + 0] = 0.0f;
	textures[index * 36 + 14 * 2 + 1] = 1.0f;
	/// --------------------------------------------------------
	/// Vert #1 -- triangle 6
	// Verts
	vertices[index * 54 + 15 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 15 * 3 + 1] = o.y + yPlus;
	vertices[index * 54 + 15 * 3 + 2] = o.z + sin30 * zHalfSize;
	// Normals
	normals[index * 54 + 15 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 15 * 3 + 1] = 0.0f;
	normals[index * 54 + 15 * 3 + 2] = 1.732f / 1.999956f;
	// Colour
	colours[index * 72 + 15 * 4 + 0] = 0.0f;
	colours[index * 72 + 15 * 4 + 1] = 0.0f;
	colours[index * 72 + 15 * 4 + 2] = 0.0f;
	colours[index * 72 + 15 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 15 * 2 + 0] = 0.0f;
	textures[index * 36 + 15 * 2 + 1] = 1.0f;
	/// Vert #2 -- triangle 6
    // Verts
	vertices[index * 54 + 16 * 3 + 0] = o.x + -cos30 * xHalfSize;
	vertices[index * 54 + 16 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 16 * 3 + 2] = o.z + sin30 * zHalfSize;
    // Normals
	normals[index * 54 + 16 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 16 * 3 + 1] = 0.0f;
	normals[index * 54 + 16 * 3 + 2] = 1.732f / 1.999956f;
    // Color
	colours[index * 72 + 16 * 4 + 0] = 1.0f;
	colours[index * 72 + 16 * 4 + 1] = 1.0f;
	colours[index * 72 + 16 * 4 + 2] = 1.0f;
	colours[index * 72 + 16 * 4 + 3] = 1.0f;
    // Texture
	textures[index * 36 + 16 * 2 + 0] = 0.0f;
	textures[index * 36 + 16 * 2 + 1] = 0.0f;
	/// Vert #3 -- triangle 6
	// Verts
	vertices[index * 54 + 17 * 3 + 0] = o.x + cos30 * xHalfSize;
	vertices[index * 54 + 17 * 3 + 1] = o.y + yMinus;
	vertices[index * 54 + 17 * 3 + 2] = o.z + -sin30 * zHalfSize;
	// Normals
	normals[index * 54 + 17 * 3 + 0] = 1.0f / 1.999956f;
	normals[index * 54 + 17 * 3 + 1] = 0.0f;
	normals[index * 54 + 17 * 3 + 2] = 1.732f / 1.999956f;
	// Colour
	colours[index * 72 + 17 * 4 + 0] = 1.0f;
	colours[index * 72 + 17 * 4 + 1] = 1.0f;
	colours[index * 72 + 17 * 4 + 2] = 1.0f;
	colours[index * 72 + 17 * 4 + 3] = 1.0f;
	// Texture
	textures[index * 36 + 17 * 2 + 0] = 1.0f;
	textures[index * 36 + 17 * 2 + 1] = 0.0f;
	/// --------------------------------------------------------
}

void Grass::createVBO(glm::vec3 center, float range)
{
	std::string vertPath = buildPath("res/shaders/grassy_wind.vert");
	std::string fragPath = buildPath("res/shaders/grassy_wind.frag");
	this->grassShader = createShader(&vertPath, &fragPath);

    using namespace gl;
    GLuint stride = 3 * 4 + 3 * 4 + 4 * 4 + 2 * 4;
    GLuint totalElementsOfData = 3 + 3 + 4 + 2;

    /// 6 verts per quad; 3 quads per cluster = 18 verts.
    /// 
    /// use [floor(sqrt(density)) + 1] * 2 number of nodes.
    int numberPerDimension = static_cast<int>(sqrt(density)) + 1;
    int numberOfClusters = (numberPerDimension * numberPerDimension);
	float* vertices = new float[numberOfClusters * 18 * 3];
	float* normals = new float[numberOfClusters * 18 * 3];
	float* textures = new float[numberOfClusters * 18 * 2];
	float* colours = new float[numberOfClusters * 18 * 4];
    int cx = center.x;
    int cz = center.z;
    int minX = cx - range;
    int minZ = cz - range;
    int maxX = cx + range;
    int maxZ = cz + range;
    for(int i = 0; i < numberPerDimension; i++)
    {
        for(int j = 0; j < numberPerDimension; j++)
        {
            int index = i * numberPerDimension + j;
            glm::vec3 v(
				((range * 2) / numberPerDimension) * i + minX + randomizationOffsets.x * getRandomFloat(),
				0 + randomizationOffsets.y * getRandomFloat(),
				((range * 2) / numberPerDimension) * j + minZ + randomizationOffsets.z * getRandomFloat()
			);
			putGrassCluster(vertices, normals, colours, textures, index, v);
        }
    }
	this->vao = std::shared_ptr<TexturedNormalColouredVAO>(new TexturedNormalColouredVAO(
		grassShader->programID, numberOfClusters * 18,
		vertices, numberOfClusters * 18 * 3 * sizeof(float),
		normals, numberOfClusters * 18 * 3 * sizeof(float),
		colours, numberOfClusters * 18 * 4 * sizeof(float),
		textures, numberOfClusters * 18 * 2 * sizeof(float)
	));
    this->vao->tex = texture;
}

float Grass::getWindPower()
{
    float percent = clamp(static_cast<float>(maxTimeOfCurrentBurst - remainingTime) / static_cast<float>(maxTimeOfCurrentBurst));
    if(percent <= 0.2f)
    {
        return (clamp((percent / 0.2f)) * maxWindPower);
    }
    else if(percent >= 0.8f)
    {
        float powerFactor = clamp((1.0f - percent) / 0.2f);
        return (powerFactor * maxWindPower);
    }
    else
    {
        float range = 0.2f;
        float range2 = range / 2.0f;
        // Cheap and dirty fmod() calculation
        while(percent > range)
        {
            percent -= 0.2f;
        }
        float powerFactor = percent;
        if(powerFactor < range2)
        {
            return (1.0f - 0.3f * clamp(powerFactor / range2)) * maxWindPower;
        }
        else
        {
            powerFactor -= range2;
            return (0.7f + clamp(powerFactor / range2) * 0.3f) * maxWindPower;
        }
    }
}
