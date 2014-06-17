/* Class representing a point light */

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

/* The maximum number of point lights allowed (must correspond with the
number in the fragment shader). */
#define MAX_POINT_LIGHTS 4

class PointLight : public Light {
public:
	/* Creates a new PointLight with the specified ambient, diffuse, and specular terms at the
	specified position. Reports an error if the maximum number of lights has been created already. */
	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

private:
	/* Update the ambient uniform for this light */
	virtual void updateAmbientUniform();

	/* Update the diffuse uniform for this light */
	virtual void updateDiffuseUniform();

	/* Update the specular uniform for this light */
	virtual void updateSpecularUniform();

	/* Position of this light */
	glm::vec3 pos;

	/* Number of point light created so far. */
	static int num_plights_created;
};

#endif