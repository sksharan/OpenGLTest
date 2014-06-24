#include "KeyHandler.h"
#include "ProgramState.h"
#include "MatrixTransform.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include "Viewer.h"
#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define KEYHANDLER_DEBUG 0

const Uint8* keystate = SDL_GetKeyboardState(NULL);

bool wireframeEnabled = false;

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
}