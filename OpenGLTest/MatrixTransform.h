/* Updates the updating of uniforms for transformation matrices. */

#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

#include <GL/glew.h>

/* Sets up the perspective matrix for use in the current shaders, using the perspective matrix
in 'programState' (see ProgramState.h). Requires an OpenGL 'program'. */
void updateUniformPerspective(GLuint program);

/* Sets up the model matrix for use in the current shaders, using the model matrix
in 'programState' (see ProgramState.h). Updates normal matrix as well. Requires an OpenGL 'program'.  */
void updateUniformModel(GLuint program);

/* Sets up the view matrix for use in the current shaders, using the view matrix
in 'programState' (see ProgramState.h). Updates normal matrix as well. Requires an OpenGL 'program'. */
void updateUniformView(GLuint program);

/* Sets up the normal matrix for use in the current shaders, using the normal matrix
in 'programState' (see ProgramState.h). Requires an OpenGL 'program'.  */
void updateUniformNormal(GLuint program);

/* Updates the normal matrix in ProgramState based on the current model and
view matrices. Automatically called when updateUniformModel() or 
updateUniformView() is called. Requires an OpenGL 'program'.  */
void updateNormalMatrix(GLuint program);

#endif