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

	return new RenderableObject("test_square", vertices, texcoords, normals, indices, true, true,
		ambient, diffuse, specular, shininess, texture_filename);
}

OBJObject* genTower() {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(0.5, 0.5, 0.5, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 15.0f;

	std::string texture_filename = "textures/tower.jpg";

	std::string obj_filename = "obj/tower.obj";

	return new OBJObject("tower_obj", true, true, ambient, diffuse, specular, shininess, texture_filename, obj_filename);
}

OBJObject* genSuzanne() {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(0.5, 0.5, 0.5, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 15.0f;

	std::string texture_filename = "textures/red.jpg";

	std::string obj_filename = "obj/suzanne.obj";

	return new OBJObject("suzanne_obj", true, true, ambient, diffuse, specular, shininess, texture_filename, obj_filename);
}

OBJObject* genDragon() {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(0.5, 0.5, 0.5, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 15.0f;

	std::string texture_filename = "textures/black.jpg";

	std::string obj_filename = "obj/dragon.obj";

	return new OBJObject("dragon_obj", true, true, ambient, diffuse, specular, shininess, texture_filename, obj_filename);
}

HeightmapObject* genHeightmapObject(glm::vec3 start_loc) {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(1.0, 0.5, 0.0, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 50.0f;

	std::string texture_filename = "textures/chadvernon.jpg";

	std::string heightmap_filename = "heightmaps/chadvernon.jpg";

	int length = 256;  //since texture and heightmap images are 256 x 256 pixels
	float spacing = 0.5;
	float amplitude = 25.0;

	return new HeightmapObject("heightmap", true, true, ambient, diffuse, specular, shininess, texture_filename,
		heightmap_filename, start_loc, length, spacing, amplitude);
}

PerlinHeightmapObject* genPerlinHeightmapObject(glm::vec3 start_loc) {
	glm::vec4 ambient(1.0, 1.0, 1.0, 1.0);
	glm::vec4 diffuse(1.0, 0.5, 0.0, 1.0);
	glm::vec4 specular(1.0, 1.0, 1.0, 1.0);
	float shininess = 50.0f;

	int length = 512;
	float spacing = 0.5;
	float amplitude = 25.0;

	return new PerlinHeightmapObject("perlin_hm", true, false, ambient, diffuse, specular, shininess, start_loc, length, spacing, amplitude);
}