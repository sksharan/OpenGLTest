#include "Test.h"
#include "Constants.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

RenderableObject* createTestObject() {
	std::string name = "test object";
	std::vector<float> verts({ 0.0f, 0.5f, -5.0f, 0.5f, -0.5f, -5.0f, -0.5f, -0.5f, -5.0f });
	std::vector<float> texcoords({ 0.0f, 0.0f, 0.1f, 0.1f,  0.0f, 0.0f }); //change later
	std::vector<float> normals({ 0.0f, 0.5f, -5.0f, 0.5f, -0.5f, -5.0f, -0.5f, -0.5f, -5.0f }); //change later
	std::vector<GLuint> indices({ 0, 1, 2 });
	glm::vec4 ambient(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 diffuse(0.5f, 0.5f, 0.5f, 1.0f);
	glm::vec4 specular(0.5f, 0.5f, 0.5f, 1.0f);
	float shininess = 1.0f;
	std::string texture_filename = TEST_TEXTURE_STR_24BIT;
	RenderableObject* ro = new RenderableObject(name, verts, texcoords, normals, indices, true,
		                                        true, ambient, diffuse, specular, shininess, texture_filename);
	return ro;
}