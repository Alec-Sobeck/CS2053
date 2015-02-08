#ifndef LIGHTING_SHADER_DEMO_H
#define LIGHTING_SHADER_DEMO_H

#include <memory>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "opengl/rendersettingshelper.h"
#include "shaders/shader.h"

class LightingShaderDemo
{
public:
    bool done = false;
    std::shared_ptr<Shader> shader1;
    int numPointLights;
    int numDirectionLights;
    //length is a multiple of 4, ordering of elements: ambient, diffuse, specular, position
    std::vector<glm::vec3> pointLights;
    //length is a multiple of 4, ordering of elements: ambient, diffuse, specular, direction
    std::vector<glm::vec3> directionLights;
    void render();
    void init(int argc, char **argv);
    void initLights();
    void run(int argc, char **argv);
};



#endif
