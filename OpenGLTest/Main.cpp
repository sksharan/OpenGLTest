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

	/* Set up the OpenGL program objects. */
	GLuint default_vert_shader = createShader("shaders/default.vert", GL_VERTEX_SHADER);
	GLuint default_frag_shader = createShader("shaders/default.frag", GL_FRAGMENT_SHADER);
	GLuint landscape_vert_shader = createShader("shaders/landscape.vert", GL_VERTEX_SHADER);
	GLuint landscape_geo_shader = createShader("shaders/landscape.geo", GL_GEOMETRY_SHADER);
	GLuint landscape_frag_shader = createShader("shaders/landscape.frag", GL_FRAGMENT_SHADER);
	GLuint default_program = createProgram(default_vert_shader, default_frag_shader);
	GLuint landscape_program = createProgram(landscape_vert_shader, landscape_geo_shader, landscape_frag_shader);
	//GLuint landscape_program = createProgram(default_vert_shader, landscape_frag_shader);
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
	programState.perspectiveMatrix = glm::perspective(persp_fov, (float)mainWindow.width/(float)mainWindow.height, persp_z_near, persp_z_far);
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

	/* Create a new Scene. */
	Scene scene("test", glm::vec4(0.7, 0.76, 0.85, 1.0), 1.0);

	/* Create the objects and add them to the Scene. */
	RenderableObject* square = genTestSquare(glm::vec3(0, 1.5, -2), 6.0);
	scene.addObject(square);

	OBJObject* tower = genTower();
	scene.addObject((RenderableObject*)tower);

	OBJObject* suzanne = genSuzanne();
	scene.addObject((RenderableObject*)suzanne);

	//OBJObject* dragon = genDragon();
	//scene.addObject((RenderableObject*)dragon);

	HeightmapObject* hm = genHeightmapObject(glm::vec3(0, 0, 100));
	scene.addObject((RenderableObject*)hm);

	PerlinHeightmapObject* phm = genPerlinHeightmapObject(glm::vec3(0, 0, 0));
	scene.addObject((RenderableObject*)phm);

	/* Register the PerlinHeightmapObject as the current landscape. The user can choose to "walk" on this object. */
	landscapeManager.landscape = phm;

	/* Create the lights. */
	PointLight light1(glm::vec3(50, 25, -50), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.4, 0.4, 0.4), glm::vec3(1.0, 1.0, 1.0), 1.0);

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
	for (unsigned int i = 0; i < PerlinHeightmapObject::getPerlinHeightmapObjects().size(); i++) {
		delete PerlinHeightmapObject::getPerlinHeightmapObjects()[i];
	}

	/* Deinitialize SDL. */
	deinitSDL();

	return 0;
}