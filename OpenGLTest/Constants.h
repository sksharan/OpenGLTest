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

/* An AABB around an object named 'obj' will have the name 'obj_AABB'. */
#define AABB_SUFFIX "_AABB"

/* An OBB around an object named 'obj' will have the name 'obj_OBB'. */
#define OBB_SUFFIX "_OBB"

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

/* Controls the rate of translation for objects. */
extern float translation_factor;

/* Controls the rate of scaling for objects. */
extern float scaling_factor;

/* Controls the rate of rotation for objects. */
extern float rotation_factor;

/* The difference between the current time and the old time. Used in KeyHandler.cpp and MouseHandler.cpp. */
extern float delta_time;

#endif