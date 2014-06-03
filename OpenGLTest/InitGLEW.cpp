#include "InitGLEW.h"
#include <GL/glew.h>
#include <iostream>

bool initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(status));
		return false;
	}
	return true;
}