#include "OBJObject.h"
#include "Constants.h"
#include "Util.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

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

	parseOBJ();

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
				size_t v_index = atoi(str.substr(0, first_slash).c_str()) - 1;
				size_t vt_index = atoi(str.substr(first_slash + 1, second_slash).c_str()) - 1;
				size_t vn_index = atoi(str.substr(second_slash + 1, str.size()).c_str()) - 1;

				temp_v_indices.push_back(v_index);
			    temp_vt_indices.push_back(vt_index);
			    vn_indices_ptr->push_back(vn_index);
			}
		}
	}
}