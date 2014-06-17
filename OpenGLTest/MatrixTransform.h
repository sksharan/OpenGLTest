/* Updates the updating of uniforms for transformation matrices. */

#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

/* Sets up the perspective matrix for use in the current shaders. */
void updateUniformPerspective();

/* Sets up the modelview matrix for use in the current shaders. */
void updateUniformModelview();

/* Sets up the normal matrix for use in the current shaders. */
void updateUniformNormal();

#endif