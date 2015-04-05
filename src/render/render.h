#ifndef ENGINE_RENDER_H
#define ENGINE_RENDER_H

#include <map>
#include <glbinding/gl/gl.h>
#include "render/texture.h"
#include "graphics/camera.h"
#include "graphics/gluhelper.h"
#include "utils/textureloader.h"
#include "physics/aabb.h"

/**
 * Defines the base class for anything that draws something to screen in this application. All Textures are stored here.
 * as public static fields.
 * @author      Alec Sobeck
 */
class Render
{
private:
	 //std::map<std::string, Texture*> texturesByName;

public:
	 Texture paletteIcons;
	 Texture sun;
	 Texture pyro;
	 Texture redX;
	 Texture mainMenuBackground;
	 Texture terrain;
	/**
	 * Loads all game textures in use by Render and all extensions. This cannot be threaded.
	 */
	void initializeTextures();
	/**
	 * Gets a Texture already loaded by its name.
	 * @param name a String that is the name of the Texture. This is the name of the file the Texture was loaded from
	 * @return a Texture with the specified name if one exists, otherwise null
	 */
	Texture* getTexture(std::string name);
	/**
	 * Loads a Texture from file and handles access to the textureByName HashMap. This should be used to load all Textures.
	 * @param ref a String that is the relative file path of the resource to load, from within the jar file
	 * @return a Texture created from the provided file path
	 */
	Texture* loadTexture(std::string ref);

};

void drawSkybox(std::shared_ptr<Texture> skybox, Camera *cam);
void renderAxes(Camera *cam);
void drawAABB(AABB &box);

#endif
