#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

/* The following functions depend on the state of 'programState'
 * (see ProgramState.h) */

/* Sets up the perspective matrix for use in the current shaders. */
void updateUniformPerspective();

/* Sets up the modelview matrix for use in the current shaders. */
void updateUniformModelview();

#endif