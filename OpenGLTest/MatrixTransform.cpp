#include "MatrixTransform.h"
#include "ProgramState.h"
#include "Constants.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#define MATRIXTRANSFORM_DEBUG 0

void updateUniformModel(GLuint program) {
	GLuint model_uni_loc = glGetUniformLocation(program, MODEL_UNIFORM_STR);
	if (MATRIXTRANSFORM_DEBUG && model_uni_loc == -1) {
		std::cout << "error in updating model uniform" << std::endl;
	}
	glUseProgram(program);
	glUniformMatrix4fv(model_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.modelMatrix));
	glUseProgram(0);

	updateNormalMatrix(program);
	updateUniformNormal(program);
}

void updateUniformView(GLuint program) {
	GLuint view_uni_loc = glGetUniformLocation(program, VIEW_UNIFORM_STR);
	if (MATRIXTRANSFORM_DEBUG && view_uni_loc == -1) {
		std::cout << "error in updating model uniform" << std::endl;
	}
	glUseProgram(program);
	glUniformMatrix4fv(view_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.viewMatrix));
	glUseProgram(0);

	updateNormalMatrix(program);
	updateUniformNormal(program);
}

void updateUniformPerspective(GLuint program) {
	GLuint persp_uni_loc = glGetUniformLocation(program, PERSPECTIVE_UNIFORM_STR);
	if (MATRIXTRANSFORM_DEBUG && persp_uni_loc == -1) {
		std::cout << "error in updating perspective uniform" << std::endl;
	}
	glUseProgram(program);
	glUniformMatrix4fv(persp_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.perspectiveMatrix));
	glUseProgram(0);
}

void updateUniformNormal(GLuint program) {
	GLuint normal_uni_loc = glGetUniformLocation(program, NORMAL_UNIFORM_STR);
	if (MATRIXTRANSFORM_DEBUG && normal_uni_loc == -1) {
		std::cout << "error in updating normal uniform" << std::endl;
	}
	glUseProgram(program);
	glUniformMatrix3fv(normal_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.normalMatrix));
	glUseProgram(0);
}

void updateNormalMatrix(GLuint program) {
	programState.normalMatrix = glm::inverseTranspose(glm::mat3(programState.viewMatrix * programState.modelMatrix));
}