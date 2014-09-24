/* Implementation of functions declared in InitGL.h. */

#include "InitGL.h"
#include "Util.h"
#include <GL/glew.h>
#include <string>
#include <iostream>

void setupGLEnables() {
    //depth buffering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //backface culling
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);*/

    //blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLuint createShader(std::string shader_filename, GLenum shader_type) {
    std::string str_shader_data = readFile(shader_filename);
    const char* shader_data = str_shader_data.c_str();
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_data, NULL);
    glCompileShader(shader);

    //partly adapted from http://www.arcsynthesis.org/gltut/Basics/Tut01%20Making%20Shaders.html
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = (GLchar*)malloc((infoLogLength + 1) * sizeof(char));
        glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        free(infoLog);
    }

    return shader;
}

GLuint createProgram(GLuint vert_shader, GLuint frag_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);
    return program;
}

GLuint createProgram(GLuint vert_shader, GLuint geo_shader, GLuint frag_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, geo_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);
    return program;
}