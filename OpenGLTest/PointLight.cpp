#include "PointLight.h"
#include "ProgramState.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

int PointLight::num_plights_created = 0;

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float light_intensity) 
           : Light(ambient, diffuse, specular, light_intensity) {
	pos = position;
	id = num_plights_created;

	num_plights_created++;
	if (num_plights_created > MAX_POINT_LIGHTS) {
		std::cerr << "Error: too many points lights were created" << std::endl;
		return;
	}

	std::string index_str = std::to_string(num_plights_created - 1);
	positionUniformName = "pLights[" + index_str + "].position";
	intensityUniformName = "pLights[" + index_str + "].intensity";
	ambientUniformName = "pLights[" + index_str + "].La";
	diffuseUniformName = "pLights[" + index_str + "].Ld";
	specularUniformName = "pLights[" + index_str + "].Ls";

	updatePositionUniform();
	updateIntensityUniform();
	updateAmbientUniform();
	updateDiffuseUniform();
	updateSpecularUniform();

	updateNumPLightsUniform();
}

glm::vec3 PointLight::getPosition() {
	return pos;
}

void PointLight::updatePositionUniform() {
	GLuint pos_uni_loc = glGetUniformLocation(programState.program, positionUniformName.c_str());
	if (pos_uni_loc == -1) {
		std::cout << "error in updating light position uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform3fv(pos_uni_loc, 1, glm::value_ptr(pos));
	glUseProgram(0);
}

void PointLight::updateAmbientUniform() {
	GLuint ambient_uni_loc = glGetUniformLocation(programState.program, ambientUniformName.c_str());
	if (ambient_uni_loc == -1) {
		std::cout << "error in updating light ambient uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform3fv(ambient_uni_loc, 1, glm::value_ptr(La));
	glUseProgram(0);
}

void PointLight::updateDiffuseUniform() {
	GLuint diffuse_uni_loc = glGetUniformLocation(programState.program, diffuseUniformName.c_str());
	if (diffuse_uni_loc == -1) {
		std::cout << "error in updating light diffuse uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform3fv(diffuse_uni_loc, 1, glm::value_ptr(Ld));
	glUseProgram(0);
}

void PointLight::updateSpecularUniform() {
	GLuint specular_uni_loc = glGetUniformLocation(programState.program, specularUniformName.c_str());
	if (specular_uni_loc == -1) {
		std::cout << "error in updating light specular uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform3fv(specular_uni_loc, 1, glm::value_ptr(Ls));
	glUseProgram(0);
}

void PointLight::updateIntensityUniform() {
	GLuint intensity_uni_loc = glGetUniformLocation(programState.program, intensityUniformName.c_str());
	if (intensity_uni_loc == -1) {
		std::cout << "error in updating light intensity uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform1f(intensity_uni_loc, intensity);
	glUseProgram(0);
}

void PointLight::updateNumPLightsUniform() {
	GLuint plights_uni_loc = glGetUniformLocation(programState.program, "numPLights");
	if (plights_uni_loc == -1) {
		std::cout << "error in updating num point lights uniform" << std::endl;
	}
	glUseProgram(programState.program);
	glUniform1i(plights_uni_loc, num_plights_created);
	glUseProgram(0);
}