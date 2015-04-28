
#include "render/render.h"
#include "graphics/model.h"
#include "world/meshbuilder.h"
#include "graphics/gluhelper.h"
#include "render/vao.h"


void drawSkybox(std::shared_ptr<Shader> skyboxShader, std::shared_ptr<Texture> skyboxTexture, Camera *cam)
{
	using namespace gl;
	static bool initialized = false;
	static std::shared_ptr<TexturedNormalColouredVAO> vao;

	if (!initialized)
	{
		initialized = true;
		

		float normalData[] = {
			 //  nx     ny     nz   
			 // back quad
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 0.0f, 1.0f,

			 // front quad
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,
			 0.0f, 0.0f, -1.0f,

			 // left quad
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,
			 -1.0f, 0.0f, 0.0f,

			 // right quad
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f,

			 // top quad
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,

			 // bottom quad
			 0.0f, -1.0f, 0.0f,
			 0.0f, -1.0f, 0.0f,
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
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // front quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // left quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // right quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // top quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,

			 // bottom quad
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f,
			 1.0f, 1.0f, 1.0f, 1.0f
		 };


		 float vertexData[] = {
			 //   x      y      z    
			 // back quad
			 -100.0f, -101.0f, 100.0f,
			 -100.0f, 101.0f, 100.0f,
			 100.0f, 101.0f, 100.0f,
			 100.0f, 101.0f, 100.0f,
			 100.0f, -101.0f, 100.0f,
			 -100.0f, -101.0f, 100.0f,
			 // front quad
			 -100.0f, -100.0f, -100.0f,
			 -100.0f, 100.0f, -100.0f,
			 100.0f, 100.0f, -100.0f,
			 100.0f, 100.0f, -100.0f,
			 100.0f, -100.0f, -100.0f,
			 -100.0f, -100.0f, -100.0f,
			 // left quad
			 -100.0f, -101.0f, 100.0f,
			 -100.0f, 101.0f, 100.0f,
			 -100.0f, 101.0f, -100.0f,
			 -100.0f, 101.0f, -100.0f,
			 -100.0f, -101.0f, -100.0f,
			 -100.0f, -101.0f, 100.0f,
			 // right quad
			 100.0f, -101.0f, 100.0f,
			 100.0f, 101.0f, 100.0f,
			 100.0f, 101.0f, -100.0f,
			 100.0f, 101.0f, -100.0f,
			 100.0f, -101.0f, -100.0f,
			 100.0f, -101.0f, 100.0f,
			 // top quad
			 -101.0f, 100.0f, -101.0f,
			 -101.0f, 100.0f, 101.0f,
			 101.0f, 100.0f, 101.0f,
			 101.0f, 100.0f, 101.0f,
			 101.0f, 100.0f, -101.0f,
			 -101.0f, 100.0f, -101.0f,
			 // bottom quad
			 -101.0f, -100.0f, -101.0f,
			 -101.0f, -100.0f, 101.0f,
			 101.0f, -100.0f, 101.0f,
			 101.0f, -100.0f, 101.0f,
			 101.0f, -100.0f, -101.0f,
			 -101.0f, -100.0f, -101.0f
		 };
		 float textureCoordData[] = {
			 //  u		v
			 // back quad
			 1.0f, 0.333f,
			 1.0f, 0.666f,
			 0.75f, 0.666f,
			 0.75f, 0.666f,
			 0.75f, 0.333f,
			 1.0f, 0.333f,

			 // front quad
			 0.25f, 0.333f,
			 0.25f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, 0.333f,
			 0.25f, 0.333f,

			 // left quad
			 0.0f, 0.333f,
			 0.0f, 0.666f,
			 0.25f, 0.666f,
			 0.25f, 0.666f,
			 0.25f, 0.333f,
			 0.0f, 0.333f,

			 // right quad
			 0.75f, 0.333f,
			 0.75f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, 0.666f,
			 0.5f, .333f,
			 0.75f, 0.333f,

			 // top quad
			 0.25f, 0.666f,
			 0.25f, 1.0f,
			 0.5f, 1.0f,
			 0.5f, 1.0f,
			 0.5f, 0.666f,
			 0.25f, 0.666f,

			 // bottom quad
			 0.25f, 0.333f,
			 0.25f, 0.0f,
			 0.5f, 0.0f,
			 0.5f, 0.0f,
			 0.5f, 0.333f,
			 0.25f, 0.333f
		 };
		 
		 vao = std::shared_ptr<TexturedNormalColouredVAO>(new TexturedNormalColouredVAO(
			 skyboxShader->programID, 36, vertexData, sizeof(vertexData), normalData, sizeof(normalData), 
			 colourData, sizeof(colourData), textureCoordData, sizeof(textureCoordData)
		 ));
	 }
	 
	 glDisable(GL_CULL_FACE);
	 skyboxTexture->bind();
	 vao->draw();
	 glEnable(GL_CULL_FACE);
}

 void renderAxes(Camera *cam)
{
    using namespace gl;
    glLoadIdentity();
//    setLookAt(cam);
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
