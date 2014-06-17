#include "Light.h"

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float light_intensity) {
	La = ambient;
	Ld = diffuse;
	Ls = specular;
	intensity = light_intensity;
}

glm::vec3 Light::getAmbient() {
	return La;
}

glm::vec3 Light::getDiffuse() {
	return Ld;
}

glm::vec3 Light::getSpecular() {
	return Ls;
}

float Light::getIntensity() {
	return intensity;
}