#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include <memory>
#include "render/texture.h"

std::shared_ptr<Texture> getTexture(std::string);

#endif
