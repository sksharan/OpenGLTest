/* Defines a struct for windows and declares the main window used in the program. */

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

/* Parameters used to construct the main window. */
const std::string WINDOW_NAME = "OpenGLTest";
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int WINDOW_XPOS = SDL_WINDOWPOS_UNDEFINED;
const int WINDOW_YPOS = SDL_WINDOWPOS_UNDEFINED;

struct Window {
    /* Pointer to the window that SDL creates. */
    SDL_Window* window;
    /* OpenGL context associated with the window. */
    SDL_GLContext glContext;

    /* Name of the window. */
    std::string name;
    /* Window width. */
    int width;
    /* Window height.*/
    int height;
    /* x-position of the window */
    int xpos;
    /* y-position of the window. */
    int ypos;
};

/* The main window used in the program. */
extern Window mainWindow;

#endif