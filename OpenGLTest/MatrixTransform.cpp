#include "MatrixTransform.h"
#include "ProgramState.h"
#include "Constants.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

void updateUniformModel() {
	GLuint model_uni_loc = glGetUniformLocation(programState.program, MODEL_UNIFORM_STR);
	if (model_uni_loc == -1) {
		std::cout << "error in updating model uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniformMatrix4fv(model_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.modelMatrix));
	glUseProgram(0);

	updateNormalMatrix();
}

void updateUniformView() {
	GLuint view_uni_loc = glGetUniformLocation(programState.program, VIEW_UNIFORM_STR);
	if (view_uni_loc == -1) {
		std::cout << "error in updating model uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniformMatrix4fv(view_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.viewMatrix));
	glUseProgram(0);

	updateNormalMatrix();
}

void updateUniformPerspective() {
	GLuint persp_uni_loc = glGetUniformLocation(programState.program, PERSPECTIVE_UNIFORM_STR);
	if (persp_uni_loc == -1) {
		std::cout << "error in updating perspective uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniformMatrix4fv(persp_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.perspectiveMatrix));
	glUseProgram(0);
}

void updateUniformNormal() {
	GLuint normal_uni_loc = glGetUniformLocation(programState.program, NORMAL_UNIFORM_STR);
	if (normal_uni_loc == -1) {
		std::cout << "error in updating normal uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniformMatrix3fv(normal_uni_loc, 1, GL_FALSE, glm::value_ptr(programState.normalMatrix));
	glUseProgram(0);
}

void updateNormalMatrix() {
	programState.normalMatrix = glm::inverseTranspose(glm::mat3(programState.viewMatrix * programState.modelMatrix));
}