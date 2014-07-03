#include "KeyHandler.h"
#include "ProgramState.h"
#include "MatrixTransform.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include "Viewer.h"
#include "RenderableObject.h"
#include "EnumRenderMode.h"
#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define KEYHANDLER_DEBUG 0

const Uint8* keystate = SDL_GetKeyboardState(NULL);

/* True iff wireframe mode is enabled. */
bool wireframeEnabled = false;

/* The currently selected object. */
RenderableObject* currObject;
/* 'currObject' is RenderableObject::getRenderableObjects()[objectIndex]. */
unsigned int objectIndex = 0;

/* Function protoypes. */
void handleObjects(SDL_Event event);

/* Adapted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
void handleKeyInput() {
	/* W : move forward */
	if (keystate[SDL_SCANCODE_W]) {
		glm::vec3 position = mainViewer.getPosition();
		position += mainViewer.getDirection() * delta_time * movement_speed;
		mainViewer.setPosition(position);
		if (KEYHANDLER_DEBUG) {
			printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
		}
	}

	/* A : move left */
	if (keystate[SDL_SCANCODE_A]) {
		glm::vec3 position = mainViewer.getPosition();
		position -= mainViewer.getRightVector() * delta_time * movement_speed;
		mainViewer.setPosition(position);
		if (KEYHANDLER_DEBUG) {
			printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
		}
	}

	/* S : move backward */
	if (keystate[SDL_SCANCODE_S]) {
		glm::vec3 position = mainViewer.getPosition();
		position -= mainViewer.getDirection() * delta_time * movement_speed;
		mainViewer.setPosition(position);
		if (KEYHANDLER_DEBUG) {
			printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
		}
	}

	/* D : move right */
	if (keystate[SDL_SCANCODE_D]) {
		glm::vec3 position = mainViewer.getPosition();
		position += mainViewer.getRightVector() * delta_time * movement_speed;
		mainViewer.setPosition(position);
		if (KEYHANDLER_DEBUG) {
			printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
		}
	}
}

void handleKeyInputNC(SDL_Event event) {
	switch (event.key.keysym.sym) {

    /* ESC: exit program */
	case SDLK_ESCAPE:
		programState.done = true;
		break;

	/* T : toggle wirframe mode on/off */
	case SDLK_t:
		if (wireframeEnabled) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		wireframeEnabled = !wireframeEnabled;
		break;

	default:
		break;
	}

	handleObjects(event);
}

/* Function that specifically handles selection and manipulation of objects, given
an SDL_Event. */
void handleObjects(SDL_Event event) {
	int numRenderableObjects = RenderableObject::getRenderableObjects().size();

	/* Do nothing if there are no objects to work with. */
	if (numRenderableObjects == 0) {
		return;
	}

	/* If we have no current object, select the first object as the current object. */
	if (currObject == NULL) {
		currObject = RenderableObject::getRenderableObjects()[objectIndex];
	}

	switch (event.key.keysym.sym) {

	/* UP ARROW: go to next object. */
	case SDLK_UP:
		if (objectIndex == numRenderableObjects - 1) {
			objectIndex = 0;
		} else {
			objectIndex++;
		}
		currObject = RenderableObject::getRenderableObjects()[objectIndex];
		printf("%s now selected\n", currObject->getName().c_str());
		break;

	/* DOWN ARROW: go to previous object. */
	case SDLK_DOWN:
		if (objectIndex == 0) {
			objectIndex = numRenderableObjects - 1;
		}
		else {
			objectIndex--;
		}
		currObject = RenderableObject::getRenderableObjects()[objectIndex];
		printf("%s now selected\n", currObject->getName().c_str());
		break;

	/* R: change the rendering mode of the currently selected object. */
	case SDLK_r:
		if (currObject->getRenderMode() == RENDERMODE_NORMALS) {
			currObject->setRenderMode(RENDERMODE_TEXTURED);
		} else {
			currObject->setRenderMode(RENDERMODE_NORMALS);
		}
	default:
		break;
	}
}