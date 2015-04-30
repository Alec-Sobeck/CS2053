#pragma once

#include <map>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/camera.h"
#include "graphics/gluhelper.h"
#include "utils/textureloader.h"
#include "math/physics/aabb.h"
#include "shaders/shader.h"

void drawSkybox(std::shared_ptr<Shader> skyboxShader, std::shared_ptr<Texture> skybox, Camera *cam);
void renderAxes(Camera *cam);
void drawAABB(AABB &box);

