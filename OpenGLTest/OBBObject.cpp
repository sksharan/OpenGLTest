#include "OBBObject.h"
#include "Constants.h"

#define OBBOBJECT_DEBUG 0

std::vector<OBBObject*> OBBObject::obbObjects;

OBBObject::OBBObject(RenderableObject* obj) {
	objectName = obj->getName() + OBB_SUFFIX;

	//empty vectors would cause an error
	vertices = std::vector<float>(1);
	texcoords = std::vector<float>(1);
	normals = std::vector<float>(1);
	indices = std::vector<GLuint>(1);

	visible = true;
	light_enabled = false;

	ambient_term = glm::vec4(0.5, 0.5, 0.5, 1.0);
	diffuse_term = glm::vec4(0.5, 0.5, 0.5, 1.0);
	specular_term = glm::vec4(0.5, 0.5, 0.5, 1.0);
	shininess_term = 2.0f;

	texture_filename = "textures/OBB.png";

	object = obj;

	calculateOBB();

	initRenderableObjectEnd();
	obbObjects.push_back(this);
}

void OBBObject::calculateOBB() {
	//record minimum and maximum x, y,and z values for vertices
	float min_x = std::numeric_limits<float>::infinity();
	float max_x = -std::numeric_limits<float>::infinity();
	float min_y = std::numeric_limits<float>::infinity();
	float max_y = -std::numeric_limits<float>::infinity();
	float min_z = std::numeric_limits<float>::infinity();
	float max_z = -std::numeric_limits<float>::infinity();
	for (int i = 0; i < object->getVertices().size(); i += 3) {
		glm::vec4 vertex_pos = glm::vec4(object->getVertices()[i], object->getVertices()[i + 1], object->getVertices()[i + 2], 1.0f);

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

	if (OBBOBJECT_DEBUG) {
		printf("OBB: %f, %f, %f, %f, %f, %f\n", min_x, max_x, min_y, max_y, min_z, max_z);
	}

	//create the vertices
	std::vector<float> obb_vertices = {
		min_x, max_y, min_z, //back top left
		min_x, min_y, min_z, //back bottom left
		max_x, max_y, min_z, //back top right
		max_x, min_y, min_z, //back bottom right
		min_x, max_y, max_z, //front top left
		min_x, min_y, max_z, //front bottom left
		max_x, max_y, max_z, //front top right
		max_x, min_y, max_z //front bottom right
	};
	for (int i = 0; i < obb_vertices.size(); i+=3) {
		glm::vec4 vertex_pos = glm::vec4(obb_vertices[i], obb_vertices[i + 1], obb_vertices[i + 2], 1.0f);
		vertex_pos = object->getModelMatrix() * vertex_pos;

		obb_vertices[i] = vertex_pos.x;
		obb_vertices[i + 1] = vertex_pos.y;
		obb_vertices[i + 2] = vertex_pos.z;
	}

	//create the texcoords (these could be anything)
	std::vector<float> obb_texcoords = {
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
	std::vector<float> obb_normals = {
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
	std::vector<GLuint> obb_indices = {
		0, 2, 1, 2, 3, 1, //back face
		0, 4, 2, 2, 4, 6, //top face
		0, 1, 4, 4, 1, 5, //left face
		6, 7, 2, 2, 7, 3, //right face
		5, 3, 7, 5, 1, 3, //bottom face
		6, 4, 7, 4, 5, 7 //front face
	};

	//change this obb
	setVertices(obb_vertices);
	setTexcoords(obb_texcoords);
	setNormals(obb_normals);
	setIndices(obb_indices);
}