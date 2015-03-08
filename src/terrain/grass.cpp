#include <cmath>
#include "math/gamemath.h"
#include "terrain/grass.h"
#include "utils/random.h"
#include "utils/timehelper.h"
#include "utils/flexarray.h"
#include "graphics/gluhelper.h"
#include "graphics/terrainpolygon.h"

Grass::Grass(int density, glm::vec3 center, float range, std::shared_ptr<Texture> texture) : texture(texture), density(density), vbo(std::shared_ptr<VBO>(nullptr)),
    windDirection(glm::vec3(0, 0, 0)), maxTimeOfCurrentBurst(0), remainingTime(0), timeUntilNextBurst(0), previousTime(getCurrentTimeMillis()), deltaTime(0),
    grassShader(std::shared_ptr<Shader>(nullptr)), maxWindPower(0)
{
    seedRandomGenerator();
    createVBO(center, range);
}

void Grass::update(Camera *camera)
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

void Grass::draw(Camera *camera)
{
    using namespace gl;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//bind shader
    //if(vbo)
    //{


        glDisable(GL_BLEND);
        glAlphaFunc(GL_GREATER, 0.1f);
        glEnable(GL_ALPHA_TEST);

        glDisable(GL_CULL_FACE);
        glLoadIdentity();
        glEnable(GL_TEXTURE_2D);
        glScalef(1.0f,1.0f,1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        // Translate to model co-ordinates, based on the origin of the shape
        setLookAt(camera);

        if(grassShader)
        {
            float power = getWindPower();
      ///      std::cout << "Wind [" << power << "]" << windDirection.x << "," << windDirection.y << "," << windDirection.z << std::endl;
            vbo->hasTextureData = false;
            glEnable(GL_TEXTURE_2D);
            grassShader->bindShader();
            grassShader->glUniform1("texture1", 0);
            grassShader->glUniform3("windDirection", windDirection);
            grassShader->glUniform1("windPower", power);
            glActiveTexture(GL_TEXTURE0);
            vbo->associatedTexture->bind();

        }
        vbo->draw(camera);
        if(grassShader)
        {
            grassShader->releaseShader();
        }
        glEnable(GL_CULL_FACE);
    //}

    glDisable(GL_ALPHA_TEST);


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

inline void putGrassCluster(FlexArray<float> &combinedData, int index, glm::vec3 o/*offset*/)
{
    float sin30 = sin(toRad(30));
    float cos30 = cos(toRad(30));
    // Vert #1 -- quad1
    // Verts
    combinedData[index + 0 * 0 + 0] = o.x + 0.0f;
    combinedData[index + 0 * 0 + 1] = o.y + 0.0f;
    combinedData[index + 0 * 0 + 2] = o.z + 1.0f;
    // Normals
    combinedData[index + 0 * 0 + 3] = 1.0f;
    combinedData[index + 0 * 0 + 4] = 0.0f;
    combinedData[index + 0 * 0 + 5] = 0.0f;
    // Colour
    combinedData[index + 0 * 0 + 6] = 1.0f;
    combinedData[index + 0 * 0 + 7] = 1.0f;
    combinedData[index + 0 * 0 + 8] = 1.0f;
    combinedData[index + 0 * 0 + 9] = 1.0f;
    // Texture
    combinedData[index + 0 * 0 + 10] = 1.0f;
    combinedData[index + 0 * 0 + 11] = 0.0f;
    //Vert2 -- quad1
    // Verts
    combinedData[index + 1 * 12 + 0] = o.x + 0.0f;
    combinedData[index + 1 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 1 * 12 + 2] = o.z + 1.0f;
    // Normals
    combinedData[index + 1 * 12 + 3] = 1.0f;
    combinedData[index + 1 * 12 + 4] = 0.0f;
    combinedData[index + 1 * 12 + 5] = 0.0f;
    // Colour
    combinedData[index + 1 * 12 + 6] = 0.0f;
    combinedData[index + 1 * 12 + 7] = 0.0f;
    combinedData[index + 1 * 12 + 8] = 0.0f;
    combinedData[index + 1 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 1 * 12 + 10] = 1.0f;
    combinedData[index + 1 * 12 + 11] = 1.0f;
    //Vert3 -- quad1
    // Verts
    combinedData[index + 2 * 12 + 0] = o.x + 0.0f;
    combinedData[index + 2 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 2 * 12 + 2] = o.z + -1.0f;
    // Normals
    combinedData[index + 2 * 12 + 3] = 1.0f;
    combinedData[index + 2 * 12 + 4] = 0.0f;
    combinedData[index + 2 * 12 + 5] = 0.0f;
    // Colour
    combinedData[index + 2 * 12 + 6] = 0.0f;
    combinedData[index + 2 * 12 + 7] = 0.0f;
    combinedData[index + 2 * 12 + 8] = 0.0f;
    combinedData[index + 2 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 2 * 12 + 10] = 0.0f;
    combinedData[index + 2 * 12 + 11] = 1.0f;
    //Vert4 -- quad1
    // Verts
    combinedData[index + 3 * 12 + 0] = o.x + 0.0f;
    combinedData[index + 3 * 12 + 1] = o.y + 0.0f;
    combinedData[index + 3 * 12 + 2] = o.z + -1.0f;
    // Normals
    combinedData[index + 3 * 12 + 3] = 1.0f;
    combinedData[index + 3 * 12 + 4] = 0.0f;
    combinedData[index + 3 * 12 + 5] = 0.0f;
    // Colour
    combinedData[index + 3 * 12 + 6] = 1.0f;
    combinedData[index + 3 * 12 + 7] = 1.0f;
    combinedData[index + 3 * 12 + 8] = 1.0f;
    combinedData[index + 3 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 3 * 12 + 10] = 0.0f;
    combinedData[index + 3 * 12 + 11] = 0.0f;
///
/// Quad 2
///
    // Vert #1 -- quad2
    // Verts
    combinedData[index + 4 * 12 + 0] = o.x + cos30;
    combinedData[index + 4 * 12 + 1] = o.y + 0.0f;
    combinedData[index + 4 * 12 + 2] = o.z + sin30;
    // Normals
    combinedData[index + 4 * 12 + 3] = -1.0f / 1.999956f;
    combinedData[index + 4 * 12 + 4] = 0.0f;
    combinedData[index + 4 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 4 * 12 + 6] = 1.0f;
    combinedData[index + 4 * 12 + 7] = 1.0f;
    combinedData[index + 4 * 12 + 8] = 1.0f;
    combinedData[index + 4 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 4 * 12 + 10] = 1.0f;
    combinedData[index + 4 * 12 + 11] = 0.0f;
    //Vert2 -- quad2
    // Verts
    combinedData[index + 5 * 12 + 0] = o.x + cos30;
    combinedData[index + 5 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 5 * 12 + 2] = o.z + sin30;
    // Normals
    combinedData[index + 5 * 12 + 3] = -1.0f / 1.999956f;
    combinedData[index + 5 * 12 + 4] = 0.0f;
    combinedData[index + 5 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 5 * 12 + 6] = 0.0f;
    combinedData[index + 5 * 12 + 7] = 0.0f;
    combinedData[index + 5 * 12 + 8] = 0.0f;
    combinedData[index + 5 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 5 * 12 + 10] = 1.0f;
    combinedData[index + 5 * 12 + 11] = 1.0f;
    //Vert3 -- quad2
    // Verts
    combinedData[index + 6 * 12 + 0] = o.x + -cos30;
    combinedData[index + 6 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 6 * 12 + 2] = o.z + -sin30;
    // Normals
    combinedData[index + 6 * 12 + 3] = -1.0f / 1.999956f;
    combinedData[index + 6 * 12 + 4] = 0.0f;
    combinedData[index + 6 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 6 * 12 + 6] = 0.0f;
    combinedData[index + 6 * 12 + 7] = 0.0f;
    combinedData[index + 6 * 12 + 8] = 0.0f;
    combinedData[index + 6 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 6 * 12 + 10] = 0.0f;
    combinedData[index + 6 * 12 + 11] = 1.0f;
    //Vert4 -- quad2
    // Verts
    combinedData[index + 7 * 12 + 0] = o.x + -cos30;
    combinedData[index + 7 * 12 + 1] = o.y + 0.0f;
    combinedData[index + 7 * 12 + 2] = o.z + -sin30;
    // Normals
    combinedData[index + 7 * 12 + 3] = -1.0f / 1.999956f;
    combinedData[index + 7 * 12 + 4] = 0.0f;
    combinedData[index + 7 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 7 * 12 + 6] = 1.0f;
    combinedData[index + 7 * 12 + 7] = 1.0f;
    combinedData[index + 7 * 12 + 8] = 1.0f;
    combinedData[index + 7 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 7 * 12 + 10] = 0.0f;
    combinedData[index + 7 * 12 + 11] = 0.0f;
///
/// Quad 3
///
    // Vert #1 -- quad3
    // Verts
    combinedData[index + 8 * 12 + 0] = o.x + cos30;
    combinedData[index + 8 * 12 + 1] = o.y + 0.0f;
    combinedData[index + 8 * 12 + 2] = o.z + -sin30;
    // Normals
    combinedData[index + 8 * 12 + 3] = 1.0f / 1.999956f;
    combinedData[index + 8 * 12 + 4] = 0.0f;
    combinedData[index + 8 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 8 * 12 + 6] = 1.0f;
    combinedData[index + 8 * 12 + 7] = 1.0f;
    combinedData[index + 8 * 12 + 8] = 1.0f;
    combinedData[index + 8 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 8 * 12 + 10] = 1.0f;
    combinedData[index + 8 * 12 + 11] = 0.0f;
    //Vert2 -- quad3
    // Verts
    combinedData[index + 9 * 12 + 0] = o.x + cos30;
    combinedData[index + 9 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 9 * 12 + 2] = o.z + -sin30;
    // Normals
    combinedData[index + 9 * 12 + 3] = 1.0f / 1.999956f;
    combinedData[index + 9 * 12 + 4] = 0.0f;
    combinedData[index + 9 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 9 * 12 + 6] = 0.0f;
    combinedData[index + 9 * 12 + 7] = 0.0f;
    combinedData[index + 9 * 12 + 8] = 0.0f;
    combinedData[index + 9 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 9 * 12 + 10] = 1.0f;
    combinedData[index + 9 * 12 + 11] = 1.0f;
    //Vert3 -- quad3
    // Verts
    combinedData[index + 10 * 12 + 0] = o.x + -cos30;
    combinedData[index + 10 * 12 + 1] = o.y + 2.0f;
    combinedData[index + 10 * 12 + 2] = o.z + sin30;
    // Normals
    combinedData[index + 10 * 12 + 3] = 1.0f / 1.999956f;
    combinedData[index + 10 * 12 + 4] = 0.0f;
    combinedData[index + 10 * 12 + 5] = 1.732f / 1.999956f;
    // Colour
    combinedData[index + 10 * 12 + 6] = 0.0f;
    combinedData[index + 10 * 12 + 7] = 0.0f;
    combinedData[index + 10 * 12 + 8] = 0.0f;
    combinedData[index + 10 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 10 * 12 + 10] = 0.0f;
    combinedData[index + 10 * 12 + 11] = 1.0f;
    //Vert4 -- quad3
    // Verts
    combinedData[index + 11 * 12 + 0] = o.x + -cos30;
    combinedData[index + 11 * 12 + 1] = o.y + 0.0f;
    combinedData[index + 11 * 12 + 2] = o.z + sin30;
    // Normals
    combinedData[index + 11 * 12 + 3] = 1.0f / 1.999956f;
    combinedData[index + 11 * 12 + 4] = 0.0f;
    combinedData[index + 11 * 12 + 5] = 1.732f / 1.999956f;
    // Color
    combinedData[index + 11 * 12 + 6] = 1.0f;
    combinedData[index + 11 * 12 + 7] = 1.0f;
    combinedData[index + 11 * 12 + 8] = 1.0f;
    combinedData[index + 11 * 12 + 9] = 1.0f;
    // Texture
    combinedData[index + 11 * 12 + 10] = 0.0f;
    combinedData[index + 11 * 12 + 11] = 0.0f;
}

void Grass::createVBO(glm::vec3 center, float range)
{
    using namespace gl;
    GLuint stride = 3 * 4 + 3 * 4 + 4 * 4 + 2 * 4;
    GLuint totalElementsOfData = 3 + 3 + 4 + 2;

    /// 4 verts per quad; 3 quads per cluster = 12 verts. 12 floating point values per vert.
    /// total: 144 floats / glass cluster.
    /// use [floor(sqrt(density)) + 1] * 2 number of nodes.
    int numberPerDimension = static_cast<int>(sqrt(density)) + 1;
    int numberOfClusters = (numberPerDimension * numberPerDimension);
    FlexArray<float> combinedData(144 * numberOfClusters);
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
            glm::vec3 v(((range * 2) / numberPerDimension) * i + minX, 0, ((range * 2) / numberPerDimension) * j + minZ );
            putGrassCluster(combinedData, index * 144, v);
        }
    }
    MeshData data(GL_QUADS,
        std::shared_ptr<Material>(nullptr),
        4,
        "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/grass_1.png",
        stride,
        totalElementsOfData,
        3, 0, GL_FLOAT,
        3, 3 * 4, GL_FLOAT,
        4, 3 * 4 + 3 * 4, GL_FLOAT,
        2, 3 * 4 + 3 * 4 + 4 * 4, GL_FLOAT,
        combinedData
    );
    this->vbo = std::shared_ptr<VBO>(new VBO(data, this->texture));
    this->vbo->hasTextureData = true;
    std::string vertPath = "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/grassy_wind.vert";
    std::string fragPath = "/home/alec/Dropbox/University/GameDev/GameEngineCPP/res/grassy_wind.frag";
    this->grassShader = createShader(&vertPath, &fragPath);
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
        float powerFactor = clamp((1 - percent) / 0.2);
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
