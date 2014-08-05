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
#include "Scene.h"
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

	/* Enable mouse-look mode and force the mouse cursor to be at the center of the window. */
	programState.mouseLookModeEnabled = true;
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

	/* Create a new Scene. */
	Scene scene("test", glm::vec4(0.7, 0.7, 0.7, 1.0), 1.0);

	/* Create the objects. */
	RenderableObject* object1 = genTestSquare(glm::vec3(0, 1.5, -2), 6.0);
	RenderableObject* object2 = (RenderableObject*)genTower();
	RenderableObject* object3 = (RenderableObject*)genSuzanne();
	//RenderableObject* object4 = (RenderableObject*)genDragon();
	RenderableObject* object5 = (RenderableObject*)genHeightmapObject();

	/* Add the objects to the Scene. */
	//scene.addObject(object1);
	//scene.addObject(object2);
	scene.addObject(object3);
	//scene.addObject(object4);
	//scene.addObject(object5);

	/* Create the lights. */
	PointLight light1(glm::vec3(50, 0, 0), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.7, 0.7, 0.7), glm::vec3(1.0, 1.0, 1.0), 1.0);

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
	for (unsigned int i = 0; i < RenderableObject::getRenderableObjects().size(); i++) {
		delete RenderableObject::getRenderableObjects()[i];
	}
	for (unsigned int i = 0; i < OBJObject::getOBJObjects().size(); i++) {
		delete OBJObject::getOBJObjects()[i];
	}
	for (unsigned int i = 0; i < HeightmapObject::getHeightmapObjects().size(); i++) {
		delete HeightmapObject::getHeightmapObjects()[i];
	}
	for (unsigned int i = 0; i < AABBObject::getAABBObjects().size(); i++) {
		delete AABBObject::getAABBObjects()[i];
	}
	for (unsigned int i = 0; i < OBBObject::getOBBObjects().size(); i++) {
		delete OBBObject::getOBBObjects()[i];
	}

	/* Deinitialize SDL. */
	deinitSDL();

	return 0;
}