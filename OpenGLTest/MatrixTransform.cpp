#include "MatrixTransform.h"
#include "ProgramState.h"
#include "Constants.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void updateUniformModelview() {
	GLuint model_uni_loc = glGetUniformLocation(programState.program, MODELVIEW_UNIFORM_STR);
	glUseProgram(programState.program);
	glUniformMatrix4fv(model_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.modelviewMatrix));
	glUseProgram(0);
}

void updateUniformPerspective() {
	GLuint persp_uni_loc = glGetUniformLocation(programState.program, PERSPECTIVE_UNIFORM_STR);
	glUseProgram(programState.program);
	glUniformMatrix4fv(persp_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.perspectiveMatrix));
	glUseProgram(0);
}