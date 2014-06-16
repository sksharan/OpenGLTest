/* Definition of constants used throughout the program. */

#ifndef CONTSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

/* Name of the uniform associated with the perspective matrix. */
#define PERSPECTIVE_UNIFORM_STR "perspective"

/* Name of the uniform associated with the modelview matrix. */
#define MODELVIEW_UNIFORM_STR "modelview"

/* Name of the uniform associated with the main texture for each RenderableObject. */
#define TEXTURE_UNIFORM_STR "texture0"

/* The .obj file used to the test object. */
#define TEST_OBJECT_OBJ_STR "obj/tower.obj"

/* The name of a 24-bit image used as a texture for test objects.  */
#define TEST_TEXTURE_STR_24BIT "textures/tower.jpg"

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