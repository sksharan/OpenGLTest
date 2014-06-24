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
#include "Test.h"
#include "Util.h"
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

	/* Hide the mouse cursor. */
	SDL_ShowCursor(0);

	/* Force the mouse cursor to be at the center of the window */
	int half_width = mainWindow.width / 2;
	int half_height = mainWindow.height / 2;
	SDL_WarpMouseInWindow(mainWindow.window, half_width, half_height);

	/* Set up the GL program. */
	GLuint vert_shader = createShader("shaders/vert.txt", GL_VERTEX_SHADER);
	GLuint frag_shader = createShader("shaders/frag.txt", GL_FRAGMENT_SHADER);
	programState.program = createProgram(vert_shader, frag_shader);

	/* Set up perspective and modelview matrices. */
	programState.perspectiveMatrix = glm::perspective(persp_fov, (float)mainWindow.width/(float)mainWindow.height, persp_z_near, persp_z_far);
	programState.modelMatrix = glm::mat4();
	programState.viewMatrix = glm::mat4();
	programState.normalMatrix = glm::mat3();
	updateUniformModel();
	updateUniformView();
	updateUniformPerspective();
	updateUniformNormal();

	/* Create the objects (comment all but one of the following). */
	//RenderableObject* object = (RenderableObject*)genTestSquare();
	RenderableObject* object = (RenderableObject*)genTower();
	//RenderableObject* object = (RenderableObject*)genHeightmapObject();
	PointLight* light = genPointLight();

	/* Begin the main loop. */
	programState.done = false;
	SDL_Event event;
	while (!programState.done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				handleKeyInputNC(event);
				break;
			default:
				break;
			}
		}
		handleKeyInput();
		handleMouseInput();
		render();
	}

	/* Delete the objects (if needed). */
	delete object;

	/* Deinitialize SDL. */
	deinitSDL();

	return 0;
}