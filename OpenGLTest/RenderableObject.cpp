#include "RenderableObject.h"
#include "MatrixTransform.h"
#include <SOIL.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <limits>

#define RENDERABLEOBJECT_DEBUG 1

std::vector<RenderableObject*> RenderableObject::renderableObjects;

RenderableObject::RenderableObject(std::string name, std::vector<float>& v, std::vector<float>& t, std::vector<float>& n, std::vector<GLuint>& i, bool isVisible,
	bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess, std::string tex_filename) {

	initRenderableObjectStart(name, isVisible, lighting_enabled, ambient, diffuse, specular, shininess, tex_filename);

	vertices = v;
	texcoords = t;
	normals = n;
	indices = i;

	initRenderableObjectEnd();
}

RenderableObject::~RenderableObject() {
	if (aabb != NULL) {
		delete aabb;
	}
}

void RenderableObject::render() {
	setUniforms();
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

const std::vector<RenderableObject*>& RenderableObject::getRenderableObjects() {
	return renderableObjects;
}

std::string RenderableObject::getName() {
	return objectName;
}

const std::vector<float>& RenderableObject::getVertices() {
	return vertices;
}

void RenderableObject::setVertices(std::vector<float>& newVertices) {
	vertices = newVertices;
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo_vertices);
	initVboVertices();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

const std::vector<float>& RenderableObject::getTexcoords() {
	return texcoords;
}

void RenderableObject::setTexcoords(std::vector<float>& newTexcoords) {
	texcoords = newTexcoords;
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo_texcoords);
	initVboTexcoords();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

const std::vector<float>& RenderableObject::getNormals() {
	return normals;
}

void RenderableObject::setNormals(std::vector<float>& newNormals) {
	normals = newNormals;
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo_normals);
	initVboNormals();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

const std::vector<GLuint>& RenderableObject::getIndices() {
	return indices;
}

void RenderableObject::setIndices(std::vector<GLuint>& newIndices) {
	indices = newIndices;
	glBindVertexArray(vao);
	glDeleteBuffers(1, &vbo_indices);
	initVboIndices();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool RenderableObject::isVisible() {
	return visible;
}

void RenderableObject::toggleVisibilty() {
	visible = !visible;
}

bool RenderableObject::getLightEnabledStatus() {
	return light_enabled;
}

void RenderableObject::toggleLightEnabledStatus() {
	light_enabled = !light_enabled;
}

RenderMode RenderableObject::getRenderMode() {
	return renderMode;
}

void RenderableObject::setRenderMode(RenderMode mode) {
	renderMode = mode;
}

glm::mat4 RenderableObject::getModelMatrix() {
	return modelMatrix;
}

void RenderableObject::setModelMatrix(glm::mat4 newModelMatrix) {
	modelMatrix = newModelMatrix;
	calculateAABB();
}

void RenderableObject::enableAABB() {
	if (aabb == NULL) {
		aabb = new RenderableObject(objectName + "_AABB", std::vector<float>(1), std::vector<float>(1), std::vector<float>(1), std::vector<GLuint>(1),
			                        true, false, ambient_term, diffuse_term, specular_term, shininess_term, "textures/AABB.png");
		calculateAABB();
	}
}

RenderableObject* RenderableObject::getAABB() {
	return aabb;
}

RenderableObject::RenderableObject() {

}

void RenderableObject::initRenderableObjectStart(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse,
	glm::vec4 specular, float shininess, std::string tex_filename) {

	objectName = name;
	visible = isVisible;
	light_enabled = lighting_enabled;
	ambient_term = ambient;
	diffuse_term = diffuse;
	specular_term = specular;
	shininess_term = shininess;
	texture_filename = tex_filename;
	renderMode = RENDERMODE_TEXTURED;
	modelMatrix = glm::mat4();
	programState.modelMatrix = modelMatrix;
	aabb = NULL;
}

void RenderableObject::initRenderableObjectEnd() {
	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

void RenderableObject::initVao() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	initVboVertices();
	initVboTexcoords();
	initVboNormals();
	initVboIndices();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void RenderableObject::initVboVertices() {
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void RenderableObject::initVboTexcoords() {
	glGenBuffers(1, &vbo_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER, texcoords.size()*sizeof(float), &texcoords[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void RenderableObject::initVboNormals() {
	glGenBuffers(1, &vbo_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &normals[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void RenderableObject::initVboIndices() {
	glGenBuffers(1, &vbo_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);
}

void RenderableObject::initTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// use SOIL to get texture data
	int img_width, img_height;
	unsigned char* img_data = SOIL_load_image(texture_filename.c_str(), &img_width, &img_height, 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(img_data);
}

void RenderableObject::setUniforms() {
    updateAmbientUniform();
    updateDiffuseUniform();
	updateSpecularUniform();
	updateShininessUniform();
	updateLightEnabledUniform();
	updateRenderModeUniform();

	programState.modelMatrix = modelMatrix;
	glUseProgram(0);
	updateUniformModel();  //we need to make the glUseProgram calls because all functions in MatrixTransform.h enable the current program
	                       //update the uniforms, then disable the current program
	glUseProgram(programState.program);
}

void RenderableObject::updateAmbientUniform() {
	GLuint ambient_uni_loc = glGetUniformLocation(programState.program, "object.Ka");
	if (RENDERABLEOBJECT_DEBUG && ambient_uni_loc == -1) {
		std::cout << "error in updating object ambient uniform" << std::endl;
	}
	glUniform3fv(ambient_uni_loc, 1, glm::value_ptr(glm::vec3(ambient_term)));
}

void RenderableObject::updateDiffuseUniform() {
	GLuint diffuse_uni_loc = glGetUniformLocation(programState.program, "object.Kd");
	if (RENDERABLEOBJECT_DEBUG && diffuse_uni_loc == -1) {
		std::cout << "error in updating object diffuse uniform" << std::endl;
	}
	glUniform3fv(diffuse_uni_loc, 1, glm::value_ptr(glm::vec3(diffuse_term)));
}

void RenderableObject::updateSpecularUniform() {
	GLuint specular_uni_loc = glGetUniformLocation(programState.program, "object.Ks");
	if (RENDERABLEOBJECT_DEBUG && specular_uni_loc == -1) {
		std::cout << "error in updating object specular uniform" << std::endl;
	}
	glUniform3fv(specular_uni_loc, 1, glm::value_ptr(glm::vec3(specular_term)));
}

void RenderableObject::updateShininessUniform() {
	GLuint shininess_uni_loc = glGetUniformLocation(programState.program, "object.shininess");
	if (RENDERABLEOBJECT_DEBUG && shininess_uni_loc == -1) {
		std::cout << "error in updating object shininess uniform" << std::endl;
	}
	glUniform1f(shininess_uni_loc, shininess_term);
}

void RenderableObject::updateLightEnabledUniform() {
	GLuint lightenabled_uni_loc = glGetUniformLocation(programState.program, "object.light_enabled");
	if (RENDERABLEOBJECT_DEBUG && lightenabled_uni_loc == -1) {
		std::cout << "error in updating object light-enabled uniform" << std::endl;
	}
	if (light_enabled) {
		glUniform1i(lightenabled_uni_loc, 1);
	} else {
		glUniform1i(lightenabled_uni_loc, 0);
	}
}

void RenderableObject::updateRenderModeUniform() {
	GLuint rendermode_uni_loc = glGetUniformLocation(programState.program, "object.renderMode");
	if (RENDERABLEOBJECT_DEBUG && rendermode_uni_loc == -1) {
		std::cout << "error in updating object render mode uniform" << std::endl;
	}
	switch (renderMode) {
	case RENDERMODE_TEXTURED:
		glUniform1i(rendermode_uni_loc, 0);
		break;
	case RENDERMODE_NORMALS:
		glUniform1i(rendermode_uni_loc, 1);
		break;
	}
}

void RenderableObject::calculateAABB() {
	//do nothing if the AABB is not enabled
	if (aabb == NULL) {
		return;
	}

	//check that this object has the correct number of vertices
	if (vertices.size() % 3 != 0) {
		printf("error: number of vertices in %s is not a multiple of 3", objectName.c_str());
		return;
	}

	//record minimum and maximum x, y,and z values for vertices
	float min_x = std::numeric_limits<float>::infinity();
	float max_x = -std::numeric_limits<float>::infinity();
	float min_y = std::numeric_limits<float>::infinity();
	float max_y = -std::numeric_limits<float>::infinity();
	float min_z = std::numeric_limits<float>::infinity();
	float max_z = -std::numeric_limits<float>::infinity();
	for (int i = 0; i < vertices.size(); i += 3) {
		glm::vec4 vertex_pos = glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);
		vertex_pos = modelMatrix * vertex_pos;

		if (vertex_pos.x < min_x) {
			min_x = vertex_pos.x;
		}
		if (vertex_pos.x > max_x) {
			max_x = vertex_pos.x;
		}

		if (vertex_pos.y < min_y) {
			min_y = vertex_pos.y;
		}
		if (vertex_pos.y > max_y) {
			max_y = vertex_pos.y;
		}

		if (vertex_pos.z < min_z) {
			min_z = vertex_pos.z;
		}
		if (vertex_pos.z > max_z) {
			max_z = vertex_pos.z;
		}
	}

	if (RENDERABLEOBJECT_DEBUG) {
		printf("AABB: %f, %f, %f, %f, %f, %f\n", min_x, max_x, min_y, max_y, min_z, max_z);
	}

	//create the vertices
	std::vector<float> aabb_vertices = {
		min_x, max_y, min_z, //back top left
		min_x, min_y, min_z, //back bottom left
		max_x, max_y, min_z, //back top right
		max_x, min_y, min_z, //back bottom right
		min_x, max_y, max_z, //front top left
		min_x, min_y, max_z, //front bottom left
		max_x, max_y, max_z, //front top right
		max_x, min_y, max_z //front bottom right
	};

	//create the texcoords (these could be anything)
	std::vector<float> aabb_texcoords = {
		0.0f, 0.0f, //back top left
		0.0f, 0.0f, //back bottom left
		0.0f, 0.0f, //back top right
		0.0f, 0.0f, //back bottom right
		0.0f, 0.0f, //front top left
		0.0f, 0.0f, //front bottom left
		0.0f, 0.0f, //front top right
		0.0f, 0.0f //front bottom right
	};

	//create the normals (these could be anything)
	std::vector<float> aabb_normals = {
		1.0f, 0.0f, 0.0f, //back top left
		1.0f, 0.0f, 0.0f, //back bottom left
		1.0f, 0.0f, 0.0f, //back top right
		1.0f, 0.0f, 0.0f, //back bottom right
		1.0f, 0.0f, 0.0f, //front top left
		1.0f, 0.0f, 0.0f, //front bottom left
		1.0f, 0.0f, 0.0f, //front top right
		1.0f, 0.0f, 0.0f //front bottom right
	};

	//create the indices
	std::vector<GLuint> aabb_indices = {
		0, 2, 1, 2, 3, 1, //back face
		0, 4, 2, 2, 4, 6, //top face
		0, 1, 4, 4, 1, 5, //left face
		6, 7, 2, 2, 7, 3, //right face
		5, 3, 7, 5, 1, 3, //bottom face
		6, 4, 7, 4, 5, 7 //front face
	};

	aabb->setVertices(aabb_vertices);
	aabb->setTexcoords(aabb_texcoords);
	aabb->setNormals(aabb_normals);
	aabb->setIndices(aabb_indices);
}