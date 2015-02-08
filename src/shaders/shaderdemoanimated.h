#ifndef SHADER_DEMO_ANIMATED_H
#define SHADER_DEMO_ANIMATED_H

#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "opengl/rendersettingshelper.h"
#include "shaders/shader.h"

class ShaderDemoAnimated
{
public:
    bool done = false;
    std::shared_ptr<Shader> shader1;
    long startTime;
    void render();
    void draw();
    void init(int argc, char **argv);
    void run(int argc, char **argv);
};


#endif
