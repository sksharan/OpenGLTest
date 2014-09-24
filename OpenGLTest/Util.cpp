#include "Util.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>

std::string readFile(std::string filename) {
    /* Implementation adapted from
     * http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html */

    std::ifstream filestream;

    filestream.open(filename);
    if (!filestream.is_open()) {
        return "";
    }

    std::string str;
    filestream.seekg(0, std::ios::end);
    str.resize((unsigned int)filestream.tellg());
    filestream.seekg(0, std::ios::beg);
    filestream.read(&str[0], str.size());
    filestream.close();

    return str;
}

void checkGLError(bool print) {
    GLenum status;
    while ((status = glGetError()) != GL_NO_ERROR) {
        std::string str;

        switch (status) {
        case GL_INVALID_ENUM:
            str = "GL_INVALID_ENUM";
            break;

        case GL_INVALID_VALUE:
            str = "GL_INVALID_VALUE";
            break;

        case GL_INVALID_OPERATION:
            str = "GL_INVALID_OPERATION";
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            str = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;

        case GL_OUT_OF_MEMORY:
            str = "GL_OUT_OF_MEMORY";
            break;

        case GL_STACK_UNDERFLOW:
            str = "GL_STACK_UNDERFLOW";
            break;

        case GL_STACK_OVERFLOW:
            str = "GL_STACK_OVERFLOW";
            break;

        default:
            break;
        }

        if (print) {
            std::cerr << "Error found: " << str << std::endl;
        }
    }
}