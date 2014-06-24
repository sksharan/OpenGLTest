#include "OBJObject.h"
#include "Constants.h"
#include "Util.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

void OBJObject::render() {
	setUniforms();
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

OBJObject::OBJObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	                 float shininess, std::string tex_filename, std::string obj_filename) {

	objectName = name;
	visible = isVisible;
	light_enabled = lighting_enabled;
	ambient_term = ambient;
	diffuse_term = diffuse;
	specular_term = specular;
	shininess_term = shininess;
	texture_filename = tex_filename;
	obj_file = obj_filename;

	parseOBJ();  //initializes vertices, texcoords, normals

	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

void OBJObject::parseOBJ() {
	// open OBJ file
	std::string obj_file_data = readFile(obj_file);
	if (obj_file_data == "") {
		std::cout << obj_file << " is empty or could not be opened" << std::endl;
		return;
	}

	// set up stringstream
	std::stringstream stream;
	stream << obj_file_data;

	// create temp variables
	std::vector<float> temp_v, temp_vt, temp_vn;
	std::vector<GLuint> temp_v_indices, temp_vn_indices, temp_vt_indices;

	// read the input OBJ
	std::string str;
	while (stream >> str) {

		// ignore these lines for the time being
		if (str == "#" || str == "mtllib" || str == "o" || str == "s" || str == "usemtl") {
			std::getline(stream, str);
		}

		// read vertices
		else if (str == "v") {
			stream >> str;
			temp_v.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			temp_v.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			temp_v.push_back(static_cast<float>(atof(str.c_str())));
		}

		// read texcoords
		else if (str == "vt") {
			stream >> str;
			temp_vt.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			temp_vt.push_back(static_cast<float>(atof(str.c_str())));
		}

		// read normals
		else if (str == "vn") {
			stream >> str;
			temp_vn.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			temp_vn.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			temp_vn.push_back(static_cast<float>(atof(str.c_str())));
		}

		// read indices
		else if (str == "f") {
			for (int i = 0; i < 3; ++i) {
				stream >> str;
				size_t first_slash = str.find("/");
				size_t second_slash = str.find_last_of("/");
				size_t v_index = atoi(str.substr(0, first_slash).c_str());
				size_t vt_index = atoi(str.substr(first_slash + 1, second_slash).c_str());
				size_t vn_index = atoi(str.substr(second_slash + 1, str.size()).c_str());

				temp_v_indices.push_back(v_index);
			    temp_vt_indices.push_back(vt_index);
			    temp_vn_indices.push_back(vn_index);
			}
		}
	}

	// now we can add to our list of vertices, texcoords, normals
	for (int i = 0; i < temp_v_indices.size(); i++) {

		//note: indices in OBJ files start at 1 instead of 0
		int v_index = (temp_v_indices[i] - 1) * 3;
		int vt_index = (temp_vt_indices[i] - 1) * 2;
		int vn_index = (temp_vn_indices[i] - 1) * 3;

		vertices.push_back(temp_v[v_index]);
		vertices.push_back(temp_v[v_index + 1]);
		vertices.push_back(temp_v[v_index + 2]);

		texcoords.push_back(temp_vt[vt_index]);
		texcoords.push_back(temp_vt[vt_index + 1]);

		normals.push_back(temp_vn[vn_index]);
		normals.push_back(temp_vn[vn_index + 1]);
		normals.push_back(temp_vn[vn_index + 2]);
	}
}

/* Excludes creation of element array buffer. */
void OBJObject::initVao() {
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

