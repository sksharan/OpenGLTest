#include "Light.h"

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	La = ambient;
	Ld = diffuse;
	Ls = specular;
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