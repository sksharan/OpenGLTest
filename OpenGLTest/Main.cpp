/* Home of the main function and the main loop. */

#include "InitSDL.h"
#include "InitGLEW.h"
#include "InitGL.h"
#include "Window.h"
#include "ProgramState.h"
#include "KeyHandler.h"
#include "MouseHandler.h"
#include "Render.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include "RenderableObject.h"
#include "OBJObject.h"
#include "HeightmapObject.h"
#include "PerlinHeightmapObject.h"
#include "LandscapeManager.h"
#include "Scene.h"
#include "ObjectGenerator.h"
#include "ObjectDeleter.h"
#include "Util.h"
#include "PointLight.h"
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char** argv) {
    /* Initialize SDL. */
    if (!initSDL()) {
        return -1;
    }
    /* Initialize GLEW. */
    if (!initGLEW()) {
        return -2;
    }

    /* Enables OpenGL features as needed (e.g. depth buffering, culling, etc.) */
    setupGLEnables();

    /* Set up the OpenGL shader and program objects. */
    GLuint default_vert_shader = createShader("shaders/default.vert", GL_VERTEX_SHADER);
    GLuint default_frag_shader = createShader("shaders/default.frag", GL_FRAGMENT_SHADER);
    GLuint landscape_vert_shader = createShader("shaders/landscape.vert", GL_VERTEX_SHADER);
    GLuint landscape_geo_shader = createShader("shaders/landscape.geo", GL_GEOMETRY_SHADER);
    GLuint landscape_frag_shader = createShader("shaders/landscape.frag", GL_FRAGMENT_SHADER);
    GLuint default_program = createProgram(default_vert_shader, default_frag_shader);
    GLuint landscape_program = createProgram(landscape_vert_shader, landscape_geo_shader, landscape_frag_shader);
    programState.allPrograms.push_back(default_program);
    programState.allPrograms.push_back(landscape_program);

    /* Setup for textures. */
    for (int i = 0; i < programState.allPrograms.size(); i++) {
        GLuint program = programState.allPrograms[i];
        glUseProgram(program);
        glUniform1i(glGetUniformLocation(program, "texture0"), 0);
        glUniform1i(glGetUniformLocation(program, "texture1"), 1);
        glUniform1i(glGetUniformLocation(program, "texture2"), 2);
        glUniform1i(glGetUniformLocation(program, "texture3"), 3);
        glUniform1i(glGetUniformLocation(program, "texture4"), 4);
        glUseProgram(0);
    }

    /* Initialize the perspective, model, view, and normal matrices. We would like to use this in all of the current programs, so
    we update uniforms in all the programs. */
    programState.perspectiveMatrix = glm::perspective(persp_fov, (float)mainWindow.width / (float)mainWindow.height, persp_z_near, persp_z_far);
    programState.modelMatrix = glm::mat4();
    programState.viewMatrix = glm::mat4();
    programState.normalMatrix = glm::mat3();
    for (int i = 0; i < programState.allPrograms.size(); i++) {
        GLuint program = programState.allPrograms[i];
        updateUniformModel(program);
        updateUniformView(program);
        updateUniformPerspective(program);
        updateUniformNormal(program);
    }

    /* Create a new Scene. The objects in the Scene will all be generated at runtime. */
    Scene scene("test", glm::vec4(0.7, 0.7, 0.7, 1.0), 1.0);

    /* Register a landscape to walk on. */
    PerlinHeightmapObject* phm = genPerlinHeightmapObject(glm::vec3(0, 0, 0), 128);
    landscapeManager.registerLandscape(phm);

    /* Create the lights. */
    PointLight light1(glm::vec3(10, 10, 0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.4, 0.4, 0.4), glm::vec3(1.0, 1.0, 1.0), 1.0);

    /* Hide the mouse cursor. */
    SDL_ShowCursor(0);
    /* Enable mouse-look mode and force the mouse cursor to be at the center of the window. */
    programState.mouseLookModeEnabled = true;
    int half_width = mainWindow.width / 2;
    int half_height = mainWindow.height / 2;
    SDL_WarpMouseInWindow(mainWindow.window, half_width, half_height);

    /* Begin the main loop. */
    programState.done = false;
    SDL_Event event;
    while (!programState.done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                handleKeyInputNC(event, scene);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick(event, scene);
            default:
                break;
            }
        }
        handleKeyInput(scene);
        handleMouseMovement(scene);
        render(scene);
    }

    /* Delete all objects. */
    deleteObjects();

    /* Deinitialize SDL. */
    deinitSDL();

    return 0;
}