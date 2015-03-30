
#include "render/render.h"

#include "graphics/model.h"
#include "world/meshbuilder.h"
#include "graphics/gluhelper.h"
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

void drawSkybox(std::shared_ptr<Texture> skyboxTexture, Camera *cam)
{
	using namespace gl;
	static bool initialized = false;
	static std::shared_ptr<VBO> vbo;

	if (!initialized)
	{
		initialized = true;
		float vertexData[] = {
			 //   x      y      z    
			 // back quad
			 -100.0f, -101.0f, 100.0f,
			 -100.0f, 101.0f, 100.0f,
			 100.0f, 101.0f, 100.0f,
			 100.0f, -101.0f, 100.0f,
			 // front quad
			 -100.0f, -100.0f, -100.0f,
			 -100.0f, 100.0f, -100.0f,
			 100.0f, 100.0f, -100.0f,
			 100.0f, -100.0f, -100.0f,
			 // left quad
			 -100.0f, -101.0f, 100.0f,
			 -100.0f, 101.0f, 100.0f,
			 -100.0f, 101.0f, -100.0f,
			 -100.0f, -101.0f, -100.0f,
			 // right quad
			 100.0f, -101.0f, 100.0f,
			 100.0f, 101.0f, 100.0f,
			 100.0f, 101.0f, -100.0f,
			 100.0f, -101.0f, -100.0f,
			 // top quad
			 -101.0f, 100.0f, -101.0f,
			 -101.0f, 100.0f, 101.0f,
			 101.0f, 100.0f, 101.0f,
			 101.0f, 100.0f, -101.0f,
			 // bottom quad
			 -101.0f, -100.0f, -101.0f,
			 -101.0f, -100.0f, 101.0f,
			 101.0f, -100.0f, 101.0f,
			 101.0f, -100.0f, -101.0f,
		};

		float normalData[] = {
			 //  nx     ny     nz   
			 // back quad
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,

			 // front quad
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,

			 // left quad
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,

			 // right quad
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,

			 // top quad
			 0.0f, 1.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,
			 0.0f, 1.0f, 0.0f,

			 // bottom quad
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
		 };

		 float colourData[] = {
			 //   r      g      b      a	 
			 // back quad

			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // front quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // left quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // right quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // top quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // bottom quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f
		 };

		 float textureCoordData[] = {
			 //  u		v
			 // back quad
			 1.0f, 0.333f,
			 1.0f, 0.666f,
			 0.75f, 0.666f,
			 0.75f, 0.333f,

			 // front quad
			 0.25f, 0.333f,
			 0.25f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, 0.333f,

			 // left quad
			 0.0f, 0.333f,
			 0.0f, 0.666f,
			 0.25f, 0.666f,
			 0.25f, 0.333f,

			 // right quad
			 0.75f, 0.333f,
			 0.75f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, .333f,

			 // top quad
			 0.25f, 0.666f,
			 0.25f, 1.0f,
			 0.5f, 1.0f,
			 0.5f, 0.666f,

			 // bottom quad
			 0.25f, 0.666f,
			 0.25f, 0.333f,
			 0.5f, 0.333f,
			 0.5f, 0.666f
		 };
		 FlexArray<float> _vertexData(sizeof(vertexData) / sizeof(float));
		 FlexArray<float> _normalData(sizeof(normalData) / sizeof(float));
		 FlexArray<float> _colourData(sizeof(colourData) / sizeof(float));
		 FlexArray<float> _textureCoordData(sizeof(textureCoordData) / sizeof(float));
		 for (int i = 0; i < _vertexData.size(); i++)
		 {
			 _vertexData[i] = vertexData[i];
		 }
		 for (int i = 0; i < _normalData.size(); i++)
		 {
			 _normalData[i] = normalData[i];
		 }
		 for (int i = 0; i < _colourData.size(); i++)
		 {
			 _colourData[i] = colourData[i];
		 }
		 for (int i = 0; i < _textureCoordData.size(); i++)
		 {
			 _textureCoordData[i] = textureCoordData[i];
		 }

		 MeshData m = createModelData(GL_QUADS,
			 4,
			 "",
			 3, GL_FLOAT, GL_FLOAT, 4, GL_FLOAT, 2, GL_FLOAT,
			 _vertexData,
			 _normalData,
			 _colourData,
			 _textureCoordData
			 );
		 vbo = std::shared_ptr<VBO>(new VBO(m, skyboxTexture));
	 }

	 glPushMatrix();
	 glLoadIdentity();
	 setLookAt(cam);
	 glTranslatef(cam->getX(), cam->getY(), cam->getZ());

	 glEnable(GL_TEXTURE_2D);
	 glDisable(GL_CULL_FACE);
	 glEnableClientState(GL_VERTEX_ARRAY);
	 glEnableClientState(GL_NORMAL_ARRAY);
	 glEnableClientState(GL_COLOR_ARRAY);
	 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	 vbo->draw(cam);
	 glDisableClientState(GL_VERTEX_ARRAY);
	 glDisableClientState(GL_NORMAL_ARRAY);
	 glDisableClientState(GL_COLOR_ARRAY);
	 glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	 glEnable(GL_CULL_FACE);

	 glPopMatrix();


}

 void renderAxes(Camera *cam)
{
    using namespace gl;
    glLoadIdentity();
    setLookAt(cam);
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

void drawAABB(AABB &box)
{
	using namespace gl;
	//Multi-colored side - FRONT
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);     glVertex3f(box.xMax, box.yMin, box.zMin);      // P1 is red
	glColor3f(0.0f, 1.0f, 0.0f);     glVertex3f(box.xMax, box.yMax, box.zMin);      // P2 is green
	glColor3f(0.0f, 0.0f, 1.0f);     glVertex3f(box.xMin, box.yMax, box.zMin);      // P3 is blue
	glColor3f(1.0f, 0.0f, 1.0f);     glVertex3f(box.xMin, box.yMin, box.zMin);      // P4 is purple
	// White side - BACK
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(box.xMax, box.yMin, box.zMax);
	glVertex3f(box.xMax, box.yMax, box.zMax);
	glVertex3f(box.xMin, box.yMax, box.zMax);
	glVertex3f(box.xMin, box.yMin, box.zMax);
	// Purple side - RIGHT
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(box.xMax, box.yMin, box.zMin);
	glVertex3f(box.xMax, box.yMax, box.zMin);
	glVertex3f(box.xMax, box.yMax, box.zMax);
	glVertex3f(box.xMax, box.yMin, box.zMax);
	// Green side - LEFT
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(box.xMin, box.yMin, box.zMax);
	glVertex3f(box.xMin, box.yMax, box.zMax);
	glVertex3f(box.xMin, box.yMax, box.zMin);
	glVertex3f(box.xMin, box.yMin, box.zMin);
	// Blue side - TOP
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(box.xMax, box.yMax, box.zMax);
	glVertex3f(box.xMax, box.yMax, box.zMin);
	glVertex3f(box.xMin, box.yMax, box.zMin);
	glVertex3f(box.xMin, box.yMax, box.zMax);
	// Red side - BOTTOM
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(box.xMax, box.yMin, box.zMin);
	glVertex3f(box.xMax, box.yMin, box.zMax);
	glVertex3f(box.xMin, box.yMin, box.zMax);
	glVertex3f(box.xMin, box.yMin, box.zMin);
	glEnd();
}
