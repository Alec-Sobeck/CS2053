
#include <glbinding/gl/gl.h>
#include <vector>
#include "windowhelper.h"
#include "render/glfont.h"
#include "graphics/rendersettingshelper.h"
#include "componentbase.h"
#include "utils/utilities.h"
#include "math/gamemath.h"

ComponentBase::ComponentBase(std::shared_ptr<Texture> t, float x, float y, float width, float height)
	: renderTexture(t), x(x), y(y), width(width), height(height)
{
}

void ComponentBase::drawBackground(GLState &glState)
{
	glState.draw2DTexturedQuad(renderTexture, x, y, width, height);
}