#include "Test.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

RenderableObject* genTestSquare(glm::vec3 center_location, float scaling_factor) {
	/* Define vertices. */
	float x = center_location.x;
	float y = center_location.y;
	float z = center_location.z;

	std::vector<float> vertices = {
		x - 0.5f, y + 0.5f, z,  //top left
		x - 0.5f, y - 0.5f, z,  //bottom left
		x + 0.5f, y - 0.5f, z,  //bottom right
		x + 0.5f, y + 0.5f, z  //top right
	};

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] *= scaling_factor;
	}

	/* Define texture coordinates. */
	std::vector<float> texcoords = { 
		0.0, 1.0,  //top left
		0.0, 0.0,  //bottom left
		1.0, 0.0,  //bottom right
		1.0, 1.0  //top right
	};

	/* Define normals. */
	std::vector<float> normals = {
		0.0, 0.0, 1.0,  //top left
		0.0, 0.0, 1.0,  //bottom left
		0.0, 0.0, 1.0,  //bottom right
		0.0, 0.0, 1.0   //top right
	};

	/* Define indices.*/
	std::vector<GLuint> indices = {
		0, 1, 2,
		0, 2, 3
	};

	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(1.0, 0.5, 0.0, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 50.0f;

	std::string texture_filename = "textures/checkerboard.jpg";

	return new RenderableObject("_testSquare", vertices, texcoords, normals, indices, true, true,
		ambient, diffuse, specular, shininess, texture_filename);
}

OBJObject* genTower() {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(1.0, 0.5, 0.0, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 50.0f;

	std::string texture_filename = "textures/tower.jpg";

	std::string obj_filename = "obj/tower.obj";

	return new OBJObject("_testOBJ", true, true, ambient, diffuse, specular, shininess, texture_filename, obj_filename);
}

HeightmapObject* genHeightmapObject() {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(1.0, 0.5, 0.0, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 50.0f;

	std::string texture_filename = "textures/chadvernon.jpg";

	std::string heightmap_filename = "heightmaps/chadvernon.jpg";

	glm::vec3 start_position(0, 0, 0);

	int length = 256;  //since texture and heightmap images are 256 x 256 pixels
	float spacing = 0.5;
	float amplitude = 25.0;

	return new HeightmapObject("_testHeightmap", true, true, ambient, diffuse, specular, shininess, texture_filename,
		heightmap_filename, start_position, length, spacing, amplitude);
}

PointLight* genPointLight() {
	glm::vec3 position(0, 0, 50);
	glm::vec3 ambient(0.2, 0.2, 0.2);
	glm::vec3 diffuse(0.7, 0.7, 0.7);
	glm::vec3 specular(1.0, 1.0, 1.0);
	float intensity = 1.0;

	return new PointLight(position, ambient, diffuse, specular, intensity);
}