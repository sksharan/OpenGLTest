/* Set of functions used to get ready for rendering. */

#ifndef INITGL_H
#define INITGL_H

#include <string>
#include <GL/glew.h>

/* Enables OpenGL features as needed (e.g. depth buffering, culling, etc.) */
void setupGLEnables();

/* Creates a shader and returns a GLuint representing the shader. The shader code is
 * in 'shader_filename' and the type of shader created depends on 'shader_type'. Prints
 * an error if the shader has a complilation error. */
GLuint createShader(std::string shader_filename, GLenum shader_type);

/* Attaches the 'shaders' to a new program, links the program, and returns
 * the program */
GLuint createProgram(GLuint vert_shader, GLuint frag_shader);

#endif