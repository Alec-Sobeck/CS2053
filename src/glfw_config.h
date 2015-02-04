#ifndef GAME_GLFW_CONFIG_H
#define GAME_GLFW_CONFIG_H


#define _GLFW_USE_OPENGL
#ifdef __linux__
#define _GLFW_X11
#define _GLFW_GLX
#define _GLFW_HAS_GLXGETPROCADDRESS
#elif _WIN32
#define _GLFW_WIN32
#define _GLFW_WGL
#endif


#endif
