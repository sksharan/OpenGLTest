/* Various utility functions. */

#ifndef UTIL_H
#define UTIL_H

#include <string>

/* Returns the contents of 'filename' as a string. Returns an empty
 * string if 'filename' cannot be opened. */
std::string readFile(std::string filename);

/* Tests to see if an OpenGL related error has occured (using glGetError()) and
prints an error message only if an error did occur and 'print' is true. */
void checkGLError(bool print);

#endif