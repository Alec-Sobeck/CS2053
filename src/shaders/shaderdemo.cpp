
#include "shaders/shaderdemo.h"

void ShaderDemo::render()
{
    startRenderCycle();
    glLoadIdentity();
    draw();
    endRenderCycle();
}

void ShaderDemo::draw()
{
    shader1->bindShader();
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-0.0f, -1.0f, 0.0f);
    glEnd();
    shader1->releaseShader();

    shader2->bindShader();
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
    shader2->releaseShader();

   	glutSwapBuffers();
}

void ShaderDemo::init(int argc, char **argv)
{
    int w = 1024;
    int h = 768;

    // Create window -- "Shader Demo"
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("Shader Demo");

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (static_cast<float>(w) / static_cast<float>(h)), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    std::string fragFile = "shaders/fractal.frag";
    shader1 = createShader(nullptr, &fragFile);
    glm::vec3 v(getWindowWidth(), getWindowHeight(), 1.0);
    shader1->glUniform3("iResolution", v);
    shader1->glUniform1("shouldDrawMandel", false);

    shader2 = createShader(nullptr, &fragFile);
    shader2->glUniform3("iResolution", v);
    shader2->glUniform1("shouldDrawMandel", true);
}

void ShaderDemo::run(int argc, char **argv)
{
    init(argc, argv);
    while(!done)
    {
        render();
    }
}
