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

/* Keyboard-related controls:
	ESC : end program
	W, A, S, D : move the viewer
	Q : select previous object
	E : select next object
	R : switching rendering mode of the currently selected object
	H : toggle visibility of the currently selected object
	L : toggle whether or not the currently selected object is affected by lighting calculations
	T : toggle wireframe mode on/off
	Y : enable an AABB for the currently selected object
	Z : change to translate mode (then manipulate object with ALL ARROW KEYS, LSHIFT, SPACEBAR)
	X : change to scale mode (then manipulate object with LEFT AND RIGHT ARROW KEYS)
	C : change to rotate mode (then manipulate object with ALL ARROW KEYS)
*/

#define KEYHANDLER_DEBUG 0

const Uint8* keystate = SDL_GetKeyboardState(NULL);

/* True iff wireframe mode is enabled. */
bool wireframeEnabled = false;

/* The currently selected object. */
RenderableObject* currObject;
/* 'currObject' is RenderableObject::getRenderableObjects()[objectIndex]. */
unsigned int objectIndex = 0;

/* An enum for the different transformations that a user can make to an object. */
enum Transformation {
	TRANSLATE, SCALE, ROTATE
};
Transformation transformationMode = TRANSLATE;

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
		currObject = RenderableObject::getRenderableObjects()[0];
		printf("%s now selected\n", currObject->getName().c_str());
	}

	switch (event.key.keysym.sym) {

	/* E: go to next object. */
	case SDLK_e:
		if (objectIndex == numRenderableObjects - 1) {
			objectIndex = 0;
		} else {
			objectIndex++;
		}
		currObject = RenderableObject::getRenderableObjects()[objectIndex];
		printf("%s now selected\n", currObject->getName().c_str());
		break;

	/* Q: go to previous object. */
	case SDLK_q:
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
			printf("changing render mode of %s to RENDERMODE_TEXTURED\n", currObject->getName().c_str());
		} else {
			currObject->setRenderMode(RENDERMODE_NORMALS);
			printf("changing render mode of %s to RENDERMODE_NORMALS\n", currObject->getName().c_str());
		}
		break;

	/* H: toggle visibility of the currently selected object. */
	case SDLK_h:
		currObject->toggleVisibilty();
		break;

	/* L : toggle whether or not the currently selected object is affected by lighting calculations. */
	case SDLK_l:
		currObject->toggleLightEnabledStatus();
		break;

	/* Y : enable an AABB for the currently selected object */
	case SDLK_y:
		currObject->enableAABB();
		break;

	/* Z: switch to translate mode .*/
	case SDLK_z:
		transformationMode = TRANSLATE;
		std::cout << "switching to translation mode" << std::endl;
		break;

	/* X: switch to scale mode .*/
	case SDLK_x:
		transformationMode = SCALE;
		std::cout << "switching to scaling mode" << std::endl;
		break;

	/* C: switch to rotate mode .*/
	case SDLK_c:
		transformationMode = ROTATE;
		std::cout << "switching to rotation mode" << std::endl;
		break;

	/* UP ARROW: depends on currently selected object (see Controls comment at top of file) */
	case SDLK_UP:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, 0.0f, -translation_factor)));
		} else if (transformationMode == SCALE) {
			//does nothing
		} else if (transformationMode == ROTATE) {
			currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), rotation_factor, glm::vec3(1.0f, 0.0f, 0.0f)));
		}
		break;

	/* DOWN ARROW: depends on currently selected object (see Controls comment at top of file) */
	case SDLK_DOWN:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, 0.0f, translation_factor)));
		} else if (transformationMode == SCALE) {
			//does nothing
		} else if (transformationMode == ROTATE) {
			currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), -rotation_factor, glm::vec3(1.0f, 0.0f, 0.0f)));
		}
		break;

	/* LEFT ARROW: depends on currently selected object (see Controls comment at top of file) */
	case SDLK_LEFT:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(-translation_factor, 0.0f, 0.0f)));
		} else if (transformationMode == SCALE) {
			currObject->setModelMatrix(glm::scale(currObject->getModelMatrix(), glm::vec3(1.0/scaling_factor, 1.0/scaling_factor, 1.0/scaling_factor)));
		} else if (transformationMode == ROTATE) {
			currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), -rotation_factor, glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		break;

	/* RIGHT ARROW: depends on currently selected object (see Controls comment at top of file) */
	case SDLK_RIGHT:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(translation_factor, 0.0f, 0.0f)));
		} else if (transformationMode == SCALE) {
			currObject->setModelMatrix(glm::scale(currObject->getModelMatrix(), glm::vec3(scaling_factor, scaling_factor, scaling_factor)));
		} else if (transformationMode == ROTATE) {
			currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), rotation_factor, glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		break;

    /* LSHIFT : depends on currently selected object (see Controls comment at top of file) */
	case SDLK_LSHIFT:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, -translation_factor, 0.0f)));
		} else if (transformationMode == SCALE) {
			//does nothing
		} else if (transformationMode == ROTATE) {
			//does nothing
		}
		break;

	/* SPACEBAR : depends on currently selected object (see Controls comment at top of file) */
	case SDLK_SPACE:
		if (transformationMode == TRANSLATE) {
			currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, translation_factor, 0.0f)));
		} else if (transformationMode == SCALE) {
			//does nothing
		} else if (transformationMode == ROTATE) {
			//does nothing
		}
		break;

	default:
		break;
	}
}