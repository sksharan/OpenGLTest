#include "InitSDL.h"
#include "Window.h"
#include <iostream>

bool initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    /* We want to init OpenGL 3.3. */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    /* Properties of the created window. */
    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

    /* Create window. */
    mainWindow.window = SDL_CreateWindow(WINDOW_NAME.c_str(), WINDOW_XPOS, WINDOW_YPOS, WINDOW_WIDTH,
        WINDOW_HEIGHT, flags);

    /* Check if window created correctly. */
    if (mainWindow.window == NULL) {
        fprintf(stderr, "Error creating window: ", SDL_GetError());
        return false;
    }

    /* Create context. */
    mainWindow.glContext = SDL_GL_CreateContext(mainWindow.window);

    /* Check if context created successfully. */
    if (mainWindow.glContext == NULL) {
        fprintf(stderr, "Error creating OpenGL context: ", SDL_GetError());
        return false;
    }

    /* Initialize the rest of the members in 'mainWindow' */
    mainWindow.width = WINDOW_WIDTH;
    mainWindow.height = WINDOW_HEIGHT;
    mainWindow.xpos = WINDOW_XPOS;
    mainWindow.ypos = WINDOW_YPOS;

    return true;
}

bool deinitSDL() {
    SDL_DestroyWindow(mainWindow.window);
    SDL_Quit();
    return true;
}

