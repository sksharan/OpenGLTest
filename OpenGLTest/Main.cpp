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
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

int main(int argc, char** argv) {

	/* Initialize SDL. */
	if (!initSDL()) {
		return -1;
	}

	/* Initialize GLEW. */
	if (!initGLEW()) {
		return -2;
	}

	/* Initialize depth buffering. */
	initDepth();

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
	programState.modelviewMatrix = glm::mat4();
	programState.normalMatrix = glm::inverseTranspose(glm::mat3(programState.modelviewMatrix));
	updateUniformModelview();
	updateUniformPerspective();
	updateUniformNormal();

	/* Create the objects. */
	OBJObject object("obj_object", true, true, glm::vec4(.5, .5, .5, 1), glm::vec4(.5, .5, .5, 1), glm::vec4(.5, .5, .5, 1), 1, TEST_TEXTURE_STR_24BIT, TEST_OBJECT_OBJ_STR);
	//HeightmapObject hmobject("hm_object", true, true, glm::vec4(.5, .5, .5, 1), glm::vec4(.5, .5, .5, 1), glm::vec4(.5, .5, .5, 1), 1, "textures/chadvernon.jpg", "heightmaps/chadvernon.jpg", glm::vec3(0, 0, 0), 256, 0.5, 25.0);

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

	/* Deinitialize SDL. */
	deinitSDL();

	return 0;
}