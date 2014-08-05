/* Handles mouse input from the user. */

#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include "Scene.h"
#include <SDL.h>

/* Handles mouse movement by the user. Uses 'mainViewer' from Viewer.h */
void handleMouseMovement(Scene& scene);

/* Handles mouse clicking by the user. Uses 'mainViewer' from Viewer.h */
void handleMouseClick(SDL_Event event, Scene& scene);

#endif