/* Abstract class representing a light. */

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <string>

class Light {
public:
	/* Returns the ambient term of this light. */
	glm::vec3 getAmbient();

	/* Returns the diffuse term of this light. */
	glm::vec3 getDiffuse();

	/* Returns the specular term of this light. */
	glm::vec3 getSpecular();

	/* Returns the intensity of the light. */
	float getIntensity();

protected:
	/* Creates a new Light with the specified ambient, diffuse, and specular terms and with the
	given intensity. */
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float light_intensity);

	/* Update the ambient uniform for this light */
	virtual void updateAmbientUniform() = 0;

	/* Update the diffuse uniform for this light */
	virtual void updateDiffuseUniform() = 0;

	/* Update the specular uniform for this light */
	virtual void updateSpecularUniform() = 0;

	/* Update the intensity uniform for this light. */
	virtual void updateIntensityUniform() = 0;

	/* Ambient component of the light */
	glm::vec3 La;
	/* Diffuse component of the light */
	glm::vec3 Ld;
	/* Specular component of the light */
	glm::vec3 Ls;
	/* Intensity of the light */
	float intensity;

	/* An ID used to identify this light in the fragment shader. */
	int id;

	/* Name of the ambient uniform for this light. */
	std::string ambientUniformName;

	/* Name of the diffuse uniform for this light. */
	std::string diffuseUniformName;

	/* Name of the specular uniform for this light. */
	std::string specularUniformName;

	/* Name of the intensity uniform for this light. */
	std::string intensityUniformName;
};

#endif