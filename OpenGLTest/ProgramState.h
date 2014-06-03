#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

/* Struct representing state of the program. */
struct ProgramState {
	/* False while program is to continue running. */
	bool done;

	/* The GL program used for rendering. */
	GLuint program;

	/* The perspective matrix being used in the shaders. */
	glm::mat4 perspectiveMatrix;

	/* The modelview matrix being used in the shaders. */
	glm::mat4 modelviewMatrix;
};

extern ProgramState programState;

#endif
