#ifndef SHADER_DEMO_H
#define SHADER_DEMO_H

#include <memory>
#include "graphics/glincludes.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "graphics/rendersettingshelper.h"
#include "shaders/shader.h"

class ShaderDemo
{
public:
    bool done = false;
    std::shared_ptr<Shader> shader1;
    std::shared_ptr<Shader> shader2;
    void render();
    void draw();
    void init(int argc, char **argv);
    void run(int argc, char **argv);
};


#endif
