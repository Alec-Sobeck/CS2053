
#include <sstream>
#include "shaders/lightingshaderdemo.h"
#include "graphics/gluhelper.h"
#include "graphics/windowhelper.h"

void LightingShaderDemo::render()
{
    using namespace gl;
    startRenderCycle();
    glLoadIdentity();
    //Draw
    shader1->bindShader();
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
    shader1->releaseShader();

   	swapBuffers();
   	endRenderCycle();
}

void LightingShaderDemo::init(int argc, char **argv)
{
    using namespace gl;
    int w = 1024;
    int h = 768;
    initFreeglut(argc, argv);
    createWindow(100, 100, w, h, "Shader Demo");

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setGluPerspective(45.0f, (static_cast<float>(w)/static_cast<float>(h)),0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    initLights();

    std::string vertFilepath = "shaders/debug_vert_shader.vert";
    std::string fragFilepath = "shaders/debug_frag_shader.frag";
    shader1 = createShader(&vertFilepath, &fragFilepath);
    shader1->glUniform1("numPointLights", numPointLights);
    shader1->glUniform1("numDirectionLights", numDirectionLights);
    for(int i = 0; i < numPointLights; i++)
    {
        std::stringstream ss;
        ss << "pointLights[" << i << "]";
        shader1->glUniform3(ss.str(), pointLights[i]);
    }
    for(int i = 0; i < numDirectionLights; i++)
    {
        std::stringstream ss;
        ss << "directionLights[" << i << "]";
        shader1->glUniform3(ss.str(), directionLights[i]);
    }
}

void LightingShaderDemo::initLights()
{
    numPointLights = 0;
    numDirectionLights = 0;
    pointLights = std::vector<glm::vec3>();
    //Fill stuff in
    directionLights = std::vector<glm::vec3>();
    //Fill stuff in
}

void LightingShaderDemo::run(int argc, char **argv)
{
    init(argc, argv);
    while(!done)
    {
        render();
    }
}
