#include "PointLight.h"
#include <iostream>

int PointLight::num_plights_created = 0;

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular) {
	pos = position;
	id = num_plights_created;

	num_plights_created++;
	if (num_plights_created > MAX_POINT_LIGHTS) {
		std::cerr << "Error: too many points lights were created" << std::endl;
	}
}

void PointLight::updateAmbientUniform() {
    
}

void PointLight::updateDiffuseUniform() {

}

void PointLight::updateSpecularUniform() {

}