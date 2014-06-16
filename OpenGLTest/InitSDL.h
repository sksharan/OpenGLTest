/* Initializes SDL 2.0. */

#ifndef INITSDL_H
#define INITSDL_H

/* Initialize SDL 2.0. Returns true iff successful. Prints error message in the
* case of failure. */
bool initSDL();

/* Deinitialize SDL 2.0. Returns true iff successful. Prints error message in the 
 * case of failure. */
bool deinitSDL();

#endif