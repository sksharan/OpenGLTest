#include "Test.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

RenderableObject* genTestSquare() {
	std::vector<float> vertices = {
		-0.5, 0.5, 0.0,  //top left
		-0.5, -0.5, 0.0,  //bottom left
		0.5, -0.5, 0.0,  //bottom right
		0.5, 0.5, 0.0  //top right
	};

	float scaling_factor = 3.0f;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] *= scaling_factor;
	}

	std::vector<float> texcoords = { 
		0.0, 1.0,  //top left
		0.0, 0.0,  //bottom left
		1.0, 0.0,  //bottom right
		1.0, 1.0  //top right
	};

	std::vector<float> normals = {
		0.0, 0.0, 1.0,  //top left
		0.0, 0.0, 1.0,  //bottom left
		0.0, 0.0, 1.0,  //bottom right
		0.0, 0.0, 1.0   //top right
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		0, 2, 3
	};

	glm::vec4 ambient(0.5, 0.5, 0.5, 1.0);  //gray ambience
	glm::vec4 diffuse(0.0, 0.0, 0.8, 1.0);  //blue diffuse
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);  //white specular
	float shininess = 2.0f;

	std::string texture_filename = "textures/checkerboard.jpg";

	return new RenderableObject("_testTriangle", vertices, texcoords, normals, indices, true, true,
		ambient, diffuse, specular, shininess, texture_filename);
}