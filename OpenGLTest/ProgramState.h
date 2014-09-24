/* Defines a struct to keep track of program state (e.g. whether or not the program should
continue to run). */

#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

/* Struct representing state of the program. */
struct ProgramState {
    ProgramState() : wireframeEnabled(false), noClipEnabled(true), userHeight(2.5f) {}

    /* False while program is to continue running. */
    bool done;

    /* True iff wireframe mode is enabled. */
    bool wireframeEnabled;

    /* True iff the user can fly freely around the scene. */
    bool noClipEnabled;

    /* User's "height", used to lift the camera off of the ground when 'noClipEnabled' is false. */
    float userHeight;

    /* All OpenGL programs that were created. */
    std::vector<GLuint> allPrograms;

    /* True if the user uses the mouse to look around. If so, then SDL forces the cursor to stay at the center of the screen. */
    bool mouseLookModeEnabled;

    /* The perspective matrix being used in the shaders. */
    glm::mat4 perspectiveMatrix;

    /* The model matrix being used in the shaders (this is the modelview matrix of the current
    RenderableObject to be rendered). */
    glm::mat4 modelMatrix;

    /* The view matrix being used in the shaders. */
    glm::mat4 viewMatrix;

    /* The normal matrix being used in the shaders. */
    glm::mat3 normalMatrix;
};

extern ProgramState programState;

#endif
