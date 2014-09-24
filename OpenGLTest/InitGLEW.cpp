#include "InitGLEW.h"
#include <GL/glew.h>
#include <iostream>

#include "Util.h"

bool initGLEW() {
    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    checkGLError(false);  //toss the GL_INVALID_ENUM error
    if (status != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(status));
        return false;
    }
    return true;
}