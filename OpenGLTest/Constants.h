/* Definition of constants used throughout the program. Some variables may
be modifed in the program's lifetime. */

#ifndef CONTSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

/* Name of the uniform associated with the perspective matrix. */
#define PERSPECTIVE_UNIFORM_STR "perspectiveMatrix"

/* Name of the uniform associated with the view matrix. */
#define MODEL_UNIFORM_STR "modelMatrix"

/* Name of the uniform associated with the view matrix. */
#define VIEW_UNIFORM_STR "viewMatrix"

/* Name of the uniform associated with the normal matrix. */
#define NORMAL_UNIFORM_STR "normalMatrix"

/* Name of the uniform associated with the main texture for each RenderableObject. */
#define TEXTURE_UNIFORM_STR "texture0"

/* The .obj file used to the test object. */
#define TEST_OBJECT_OBJ_STR "obj/tower.obj"

/* The name of a 24-bit image used as a texture for test objects.  */
#define TEST_TEXTURE_STR_24BIT "textures/tower.jpg"

/* The maximum number of directional lights allowed (must correspond with the
number in the fragment shader). */
#define MAX_DIRECTIONAL_LIGHTS 2

/* The field of view used when creating the perspective matrix. */
extern float persp_fov;

/* The z-near used when creating the perspective matrix. */
extern float persp_z_near;

/* The z-far used when creating the perspective matrix. */
extern float persp_z_far;

/* How fast the viewer moves. */
extern float movement_speed;

/* Speed of the mouse. */
extern float mouse_speed;

/* Time at last update. */
extern Uint32 old_time;

/* The current time. */
extern Uint32 current_time;

/* The difference between the current time and the old time. */
extern float delta_time;

/* Angle used in calculating mouse movement. */
extern float horizontal_angle;

/* Angle used in calculating mouse movement. */
extern float vertical_angle;

#endif