#include "MouseHandler.h"
#include "Viewer.h"
#include "Window.h"
#include "ProgramState.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#define MOUSEHANDLER_DEBUG 0

/* Implementation adapted from 
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
void handleMouseInput(Scene& scene) {
	old_time = current_time;
	current_time = SDL_GetTicks();
	delta_time = float(current_time - old_time) / 1000.0f;

	// Get current mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);

	// Reset mouse position
	int half_width = mainWindow.width / 2;
	int half_height = mainWindow.height / 2;
	SDL_WarpMouseInWindow(mainWindow.window, half_width, half_height);

	// Compute new orientation
	horizontal_angle += mouse_speed * delta_time * float(mainWindow.width/2 - x);
	vertical_angle += mouse_speed * delta_time * float(mainWindow.height/2 - y);

	// Calculate direction
	glm::vec3 newDirection = glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
		                               sin(vertical_angle),
		                               cos(vertical_angle) * cos(horizontal_angle));

	// Calculate the right vector
	glm::vec3 newRightVector = glm::vec3(sin(horizontal_angle - 3.14f/2.0f),
		                                 0,
		                                 cos(horizontal_angle - 3.14f/2.0f));

	// Calculate the up vector
	glm::vec3 newUpVector = glm::cross(newRightVector, newDirection);

	// Update the Viewer's direction, right, and up vectors
	mainViewer.setDirection(newDirection);
	mainViewer.setRightVector(newRightVector);
	mainViewer.setUpVector(newUpVector);

	if (MOUSEHANDLER_DEBUG) {
		printf("viewer direction: %f, %f, %f\n", newDirection.x, newDirection.y, newDirection.z);
	}

	// Update the view matrix
	glm::mat4 viewMatrix = glm::lookAt(mainViewer.getPosition(), mainViewer.getPosition() + mainViewer.getDirection(),
		                               mainViewer.getUpVector());
	programState.viewMatrix = viewMatrix;
	updateUniformView();
}