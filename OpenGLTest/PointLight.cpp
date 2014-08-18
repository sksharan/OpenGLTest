#include "PointLight.h"
#include "ProgramState.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#define POINTLIGHT_DEBUG 0

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
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint pos_uni_loc = glGetUniformLocation(program, positionUniformName.c_str());
		if (POINTLIGHT_DEBUG && pos_uni_loc == -1) {
			std::cout << "error in updating light position uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform3fv(pos_uni_loc, 1, glm::value_ptr(pos));
		glUseProgram(0);
	}
}

void PointLight::updateAmbientUniform() {
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint ambient_uni_loc = glGetUniformLocation(program, ambientUniformName.c_str());
		if (POINTLIGHT_DEBUG && ambient_uni_loc == -1) {
			std::cout << "error in updating light ambient uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform3fv(ambient_uni_loc, 1, glm::value_ptr(La));
		glUseProgram(0);
	}
}

void PointLight::updateDiffuseUniform() {
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint diffuse_uni_loc = glGetUniformLocation(program, diffuseUniformName.c_str());
		if (POINTLIGHT_DEBUG && diffuse_uni_loc == -1) {
			std::cout << "error in updating light diffuse uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform3fv(diffuse_uni_loc, 1, glm::value_ptr(Ld));
		glUseProgram(0);
	}
}

void PointLight::updateSpecularUniform() {
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint specular_uni_loc = glGetUniformLocation(program, specularUniformName.c_str());
		if (POINTLIGHT_DEBUG && specular_uni_loc == -1) {
			std::cout << "error in updating light specular uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform3fv(specular_uni_loc, 1, glm::value_ptr(Ls));
		glUseProgram(0);
	}
}

void PointLight::updateIntensityUniform() {
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint intensity_uni_loc = glGetUniformLocation(program, intensityUniformName.c_str());
		if (POINTLIGHT_DEBUG && intensity_uni_loc == -1) {
			std::cout << "error in updating light intensity uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform1f(intensity_uni_loc, intensity);
		glUseProgram(0);
	}
}

void PointLight::updateNumPLightsUniform() {
	for (int i = 0; i < programState.allPrograms.size(); i++) {
		GLuint program = programState.allPrograms[i];

		GLuint plights_uni_loc = glGetUniformLocation(program, "numPLights");
		if (POINTLIGHT_DEBUG && plights_uni_loc == -1) {
			std::cout << "error in updating num point lights uniform" << std::endl;
		}
		glUseProgram(program);
		glUniform1i(plights_uni_loc, num_plights_created);
		glUseProgram(0);
	}
}