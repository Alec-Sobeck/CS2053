
#include <iostream>
#include "shaders/shaderdemoanimated.h"
#include "graphics/gluhelper.h"
#include "graphics/windowhelper.h"
#include "utils/timehelper.h"

void ShaderDemoAnimated::render()
{
    using namespace gl;
    startRenderCycle();
    glLoadIdentity();
    draw();
    endRenderCycle();
}

void ShaderDemoAnimated::draw()
{
    using namespace gl;
    float timeLeft = static_cast<float>(getCurrentTimeMillis() - startTime) / 1000;
    shader1->glUniform1("iGlobalTime", timeLeft);
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
}

void ShaderDemoAnimated::init(int argc, char **argv)
{
    using namespace gl;
    int w = 1024;
    int h = 768;
    initFreeglut(argc, argv);
    createWindow(100, 100, w, h, "Shader Demo");

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(45.0f, (static_cast<float>(w)/static_cast<float>(h)),0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    std::string fragFilepath = "shaders/animated1.frag";
    shader1 = createShader(nullptr, &fragFilepath);
    glm::vec3 v(getWindowWidth(), getWindowHeight(), 1.0);
    shader1->glUniform3("iResolution", v);
    shader1->glUniform1("iGlobalTime", 0.0f);
    startTime = getCurrentTimeMillis();
}

void ShaderDemoAnimated::run(int argc, char **argv)
{
    init(argc, argv);
    while(!done)
    {
        render();
    }
}

