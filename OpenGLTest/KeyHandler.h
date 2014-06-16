/* Handles keyboard input from the user. */

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <SDL.h>

/* Handles keyboard input by the user. For 'continuous' actions like moving. */
void handleKeyInput();

/* Handles keyboard input by the user. For 'non-continuous' actions like 
 * changing polygon modes. Takes an SDL_KEYDOWN event as input. */
void handleKeyInputNC(SDL_Event event);

#endif