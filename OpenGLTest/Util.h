/* Various utility functions. */

#ifndef UTIL_H
#define UTIL_H

#include <string>

/* Returns the contents of 'filename' as a string. Returns an empty
 * string if 'filename' cannot be opened. */
std::string readFile(std::string filename);

#endif