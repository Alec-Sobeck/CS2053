
#include "render/render.h"

// TODO - figure out what to do with the Render Class. Possibly remove it?


/**
 * Loads all game textures in use by Render and all extensions. This cannot be threaded.
 */
void Render::initializeTextures()
{
    static bool initialized = false;
    if(initialized)
    {
        return;
    }
    initialized = true;

    /*
    paletteIcons = loadTexture("resources/palette_icons.png");
    terrain = loadTexture("resources/terrain.png");
    sun = loadTexture("resources/sun.png");
    pyro = loadTexture("resources/pyroscavengerhunt.jpg");
    mainMenuBackground = loadTexture("resources/main_menu_background_filler.png");
    redX = loadTexture("resources/redx.png");
    */
}

/**
 * Gets a Texture already loaded by its name.
 * @param name a String that is the name of the Texture. This is the name of the file the Texture was loaded from
 * @return a Texture with the specified name if one exists, otherwise null
 */
Texture* Render::getTexture(std::string name)
{
    return nullptr;//this->texturesByName[name];
}

/**
 * Loads a Texture from file and handles access to the textureByName HashMap. This should be used to load all Textures.
 * @param ref a String that is the relative file path of the resource to load, from within the jar file
 * @return a Texture created from the provided file path
 */
 Texture* Render::loadTexture(std::string ref)
{
    /*
    Texture t = loadTexture(ref);
    if(texturesByName.containsKey(t.getAssociatedFileName()))
    {
        //This should crash the program because it indicates corrupted texture data somehow.
        throw new IllegalArgumentException("Tried to add a texture to the game, that shares a filename with some other texture @" + ref + ". Duplicate "
                + "filenames are not allowed even if in different directories");
    }
    else
    {
        texturesByName.put(t.getAssociatedFileName(), t);
    }
    return t;
    */
    return nullptr;//new Texture("", 10);
}

 void renderAxes(Camera *cam)
{
    using namespace gl;
    glLoadIdentity();
    setGluLookAt(cam);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-2000, 0, 0);
    glVertex3f(2000, 0, 0);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, -2000, 0);
    glVertex3f(0, 2000, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, -2000);
    glVertex3f(0, 0, 2000);
    glEnd();

    glEnable(GL_TEXTURE_2D);
}
