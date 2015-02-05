
#ifdef __linux__312

GLfloat    xAngle = 42.0, yAngle = 82.0, zAngle = 112.0;

void redraw(void)
{
  static GLboolean   displayListInited = GL_FALSE;

  if (displayListInited)
  {
    /* if display list already exists, just execute it */
    glCallList(1);
  }
  else
  {
    /* otherwise compile and execute to create the display list */
    glNewList(1, GL_COMPILE_AND_EXECUTE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* front face */
    glBegin(GL_QUADS);
      glColor3f(0.0, 0.7, 0.1);  /* green */
      glVertex3f(-1.0, 1.0, 1.0);
      glVertex3f(1.0, 1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(-1.0, -1.0, 1.0);

      /* back face */
      glColor3f(0.9, 1.0, 0.0);  /* yellow */
      glVertex3f(-1.0, 1.0, -1.0);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);

      /* top side face */
      glColor3f(0.2, 0.2, 1.0);  /* blue */
      glVertex3f(-1.0, 1.0, 1.0);
      glVertex3f(1.0, 1.0, 1.0);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(-1.0, 1.0, -1.0);

      /* bottom side face */
      glColor3f(0.7, 0.0, 0.1);  /* red */
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
    glEndList();
    displayListInited = GL_TRUE;
  }
}

int main(int argc, char **argv)
{
  XVisualInfo         *vi;
  Colormap             cmap;
  XSetWindowAttributes swa;
  GLXContext           cx;
  XEvent               event;
  GLboolean            needRedraw = GL_FALSE, recalcModelView = GL_TRUE;
  int                  dummy;

  /*** (1) open a connection to the X server ***/

  dpy = XOpenDisplay(NULL);
  if (dpy == NULL)
    fatalError("could not open display");

  /*** (2) make sure OpenGL's GLX extension supported ***/

  if(!glXQueryExtension(dpy, &dummy, &dummy))
    fatalError("X server has no OpenGL GLX extension");

  /*** (3) find an appropriate visual ***/

  /* find an OpenGL-capable RGB visual with depth buffer */
  vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
  if (vi == NULL)
  {
    vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);
    if (vi == NULL) fatalError("no RGB visual with depth buffer");
    doubleBuffer = GL_FALSE;
  }
  if(vi->c_class != TrueColor)
    fatalError("TrueColor visual required for this program");

  /*** (4) create an OpenGL rendering context  ***/

  /* create an OpenGL rendering context */
  cx = glXCreateContext(dpy, vi, /* no shared dlists */ None,
                        /* direct rendering if possible */ GL_TRUE);
  if (cx == NULL)
    fatalError("could not create rendering context");

  /*** (5) create an X window with the selected visual ***/

  /* create an X colormap since probably not using default visual */
  cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.event_mask = KeyPressMask    | ExposureMask
                 | ButtonPressMask | StructureNotifyMask;
  win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0,
                      300, 300, 0, vi->depth, InputOutput, vi->visual,
                      CWBorderPixel | CWColormap | CWEventMask, &swa);
  XSetStandardProperties(dpy, win, "main", "main", None,
                         argv, argc, NULL);

  /*** (6) bind the rendering context to the window ***/

  glXMakeCurrent(dpy, win, cx);

  /*** (7) request the X window to be displayed on the screen ***/

  XMapWindow(dpy, win);

  /*** (8) configure the OpenGL context for rendering ***/

  glEnable(GL_DEPTH_TEST); /* enable depth buffering */
  glDepthFunc(GL_LESS);    /* pedantic, GL_LESS is the default */
  glClearDepth(1.0);       /* pedantic, 1.0 is the default */

  /* frame buffer clears should be to black */
  glClearColor(0.0, 0.0, 0.0, 0.0);

  /* set up projection transform */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
  /* establish initial viewport */
  /* pedantic, full window size is default viewport */
  glViewport(0, 0, 300, 300);

  /*** (9) dispatch X events ***/

  while (1)
  {
    do
    {
      XNextEvent(dpy, &event);
      switch (event.type)
      {
        case KeyPress:
        {
          KeySym     keysym;
          XKeyEvent *kevent;
          char       buffer[1];
          /* It is necessary to convert the keycode to a
           * keysym before checking if it is an escape */
          kevent = (XKeyEvent *) &event;
          if (   (XLookupString((XKeyEvent *)&event,buffer,1,&keysym,NULL) == 1)
              && (keysym == (KeySym)XK_Escape) )
            exit(0);
          break;
        }
        case ButtonPress:
          recalcModelView = GL_TRUE;
          switch (event.xbutton.button)
          {
            case 1: xAngle += 10.0;
              break;
            case 2: yAngle += 10.0;
              break;
            case 3: zAngle += 10.0;
              break;
          }
          break;
        case ConfigureNotify:
          glViewport(0, 0, event.xconfigure.width,
                     event.xconfigure.height);
          /* fall through... */
        case Expose:
          needRedraw = GL_TRUE;
          break;
      }
    } while(XPending(dpy)); /* loop to compress events */

    if (recalcModelView)
    {
      glMatrixMode(GL_MODELVIEW);

      /* reset modelview matrix to the identity matrix */
      glLoadIdentity();

      /* move the camera back three units */
      glTranslatef(0.0, 0.0, -3.0);

      /* rotate by X, Y, and Z angles */
      glRotatef(xAngle, 0.1, 0.0, 0.0);
      glRotatef(yAngle, 0.0, 0.1, 0.0);
      glRotatef(zAngle, 0.0, 0.0, 1.0);

      recalcModelView = GL_FALSE;
      needRedraw = GL_TRUE;
    }
    if (needRedraw)
    {
      redraw();
      needRedraw = GL_FALSE;
    }
  }

  return 0;
}
#endif

#include <stdlib.h>
#include <string>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

bool initFreeglut(int argc, char **argv);
bool createWindow(int x, int y, int width, int height, std::string windowTitle);
void changeSize(int w, int h);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void renderScene(void);
void handleMouseClick(int button, int state, int x, int y);
void handleMouseMovementWhileClicked(int x,int y);
void handleMouseMovementWhileNotClicked(int x, int y);
void processSpecialKeys(int key, int x, int y);


float angle = 0.0f, red = 1, green = 1, blue = 1;
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations

	glLoadIdentity();
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);

        glRotatef(angle, 0.0f, 1.0f, 0.0f);

        // the function responsible for setting the color
    std::cout << red << ' ' << green << ' ' << blue << std::endl;
	glColor3f(red,green,blue);
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();
	angle+=0.1f;

	glutSwapBuffers();
}

bool initFreeglut(int argc, char **argv)
{
    glutInit(&argc, argv);

    return true;
}

bool createWindow(int x, int y, int width, int height, std::string windowTitle)
{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow(windowTitle.c_str());
    return true;
}

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y)
{
    // to check for a key modifier use:
    //       int glutGetModifiers(void);
    // The return value for this function is either one of three predefined constants or any bitwise OR combination of them. The constants are:
    //       GLUT_ACTIVE_SHIFT - Set if either you press the SHIFT key, or Caps Lock is on. Note that if they are both on then the constant is not set.
    //       GLUT_ACTIVE_CTRL - Set if you press the CTRL key.
    //       GLUT_ACTIVE_ALT - Set if you press the ALT key.


    if (key == 27)
		exit(0);
	else if (key=='r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			red = 0.0;
		else
			red = 1.0;
	}
}

/*
The first relates to which button was pressed, or released. This argument can have one of three values:

    GLUT_LEFT_BUTTON
    GLUT_MIDDLE_BUTTON
    GLUT_RIGHT_BUTTON

The second argument relates to the state of the button when the callback was generated, i.e. pressed or released. The possible values are:

    GLUT_DOWN
    GLUT_UP
*/
void handleMouseClick(int button, int state, int x, int y)
{
    // do stuff

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        red += 0.04f;
    }

}

/*
There are two types of motion that GLUT handles: active and passive motion.
Active motion occurs when the mouse is moved and a button is pressed.
*/
// "active mouse movement"
void handleMouseMovementWhileClicked(int x,int y)
{
    // Do stuff with the mouse clicked then dragged

}

// "passive mouse movement"
void handleMouseMovementWhileNotClicked(int x, int y)
{
    // Do stuff while the mouse isn't clicked, but dragged

}

void processSpecialKeys(int key, int x, int y)
{
	int mod;
	switch(key)
	{
		case GLUT_KEY_F1:
		   mod = glutGetModifiers();
		   if (mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT))
		   {   // <-- on a linux computer this will open a console you can close with control-alt-F7
		   	   red = 1.0; green = 0.0; blue = 0.0;
		   }
		   break;
		case GLUT_KEY_F2:
		   red = 0.0;
		   green = 1.0;
		   blue = 0.0;
		   break;
		case GLUT_KEY_F3:
		   red = 0.0;
		   green = 0.0;
		   blue = 1.0;
		   break;
	}
}

int main(int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutIdleFunc(renderScene);

	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);


    glutMouseFunc(handleMouseClick);
    glutMotionFunc(handleMouseMovementWhileClicked);
    glutPassiveMotionFunc(handleMouseMovementWhileNotClicked);




	// enter GLUT event processing loop
	glutMainLoop();

	return 0;
}

