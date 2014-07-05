/* Updates the updating of uniforms for transformation matrices. */

#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

/* Sets up the perspective matrix for use in the current shaders, using the perspective matrix
in 'programState' (see ProgramState.h). */
void updateUniformPerspective();

/* Sets up the model matrix for use in the current shaders, using the model matrix
in 'programState' (see ProgramState.h). Updates normal matrix as well. */
void updateUniformModel();

/* Sets up the view matrix for use in the current shaders, using the view matrix
in 'programState' (see ProgramState.h). Updates normal matrix as well. */
void updateUniformView();

/* Sets up the normal matrix for use in the current shaders, using the normal matrix
in 'programState' (see ProgramState.h). */
void updateUniformNormal();

/* Updates the normal matrix in ProgramState based on the current model and
view matrices. Automatically called when updateUniformModel() or 
updateUniformView() is called. */
void updateNormalMatrix();

#endif