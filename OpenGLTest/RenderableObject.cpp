#include "RenderableObject.h"
#include <SOIL.h>

std::vector<RenderableObject*> RenderableObject::renderableObjects;

RenderableObject::~RenderableObject() { }

void RenderableObject::render() {
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::string RenderableObject::getName() {
	return objectName;
}

const std::vector<float>& RenderableObject::getVertices() {
	return vertices;
}

const std::vector<float>& RenderableObject::getTexcoords() {
	return texcoords;
}

const std::vector<float>& RenderableObject::getNormals() {
	return normals;
}

const std::vector<GLuint>& RenderableObject::getIndices() {
	return indices;
}

bool RenderableObject::isVisible() {
	return visible;
}

void RenderableObject::toggleVisibilty() {
	visible = !visible;
}


RenderableObject::RenderableObject(std::string name, std::vector<float> v, std::vector<float> t, std::vector<float> n, std::vector<GLuint> i, bool isVisible,
	                               bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess, std::string tex_filename) {
	objectName = name;
	vertices = v;
	texcoords = t;
	normals = n;
	indices = i;
	visible = isVisible;
	light_enabled = lighting_enabled;
	ambient_term = ambient;
	diffuse_term = diffuse;
	specular_term = specular;
	shininess_term = shininess;
	texture_filename = tex_filename;

	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

RenderableObject::RenderableObject() {

}

void RenderableObject::initVao() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vbo_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER, texcoords.size()*sizeof(float), &texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RenderableObject::initTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// use SOIL to get texture data
	int img_width, img_height;
	unsigned char* img_data = SOIL_load_image(texture_filename.c_str(), &img_width, &img_height, 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(img_data);
}