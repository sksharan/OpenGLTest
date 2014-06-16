/* Defines a class representing an entity that looks into the world. */

#ifndef VIEWER_H
#define VIEWER_H

#include <glm/glm.hpp>

/* Class representing an entity that observes the world. */
class Viewer {
public:

	/* Creates a new Viewer at the origin (in world coordinates) that looks in the
	 * negative z direction. */
	Viewer();

	~Viewer();

	/* Returns the position of this Viewer. */
	glm::vec3 getPosition();

	/* Returns the direction that this Viewer is facing. */
	glm::vec3 getDirection();

	/* Returns this Viewer's right vector. */
	glm::vec3 getRightVector();

	/* Returns this Viewer's up vector. */
	glm::vec3 getUpVector();

	/* Move this Viewer to 'newPosition'.*/
	void setPosition(glm::vec3 newPosition);

	/* Set this Viewer's direction to 'newDirection'. */
	void setDirection(glm::vec3 newDirection);

	/* Set this Viewer's right vector to 'newRightVector' */
	void setRightVector(glm::vec3 newRightVector);

	/* Set this Viewer's up vector to 'newUpVector' */
	void setUpVector(glm::vec3 newUpVector);

protected:

	/* Position of this Viewer in world coordinates. */
	glm::vec3 position;

	/* Direction that this Viewer is facing. */
	glm::vec3 direction;

	/* The viewer's right vector. */
	glm::vec3 right;

	/* The viewer's up vector. */
	glm::vec3 up;
};

/* The main Viewer, which encodes where the program user is looking and where they
 * are currently located in the world. Defined in Viewer.cpp. */
extern Viewer mainViewer;

#endif