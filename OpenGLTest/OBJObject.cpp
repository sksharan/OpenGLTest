#include "OBJObject.h"
#include "Constants.h"
#include "Util.h"
#include <iostream>
#include <sstream>
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
	corrected_obj_file = CORRECTED_OBJ_FILE_PREFIX + obj_file;

	parseOBJ();

	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

void OBJObject::writeOBJ(std::string filename) {

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
			object_parse_data.vertices.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			object_parse_data.vertices.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			object_parse_data.vertices.push_back(static_cast<float>(atof(str.c_str())));
		}

		// read texcoords
		else if (str == "vt") {
			stream >> str;
			object_parse_data.texcoords.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			object_parse_data.texcoords.push_back(static_cast<float>(atof(str.c_str())));
		}

		// read normals
		else if (str == "vn") {
			stream >> str;
			object_parse_data.normals.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			object_parse_data.normals.push_back(static_cast<float>(atof(str.c_str())));
			stream >> str;
			object_parse_data.normals.push_back(static_cast<float>(atof(str.c_str())));
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
				object_parse_data.v_indices.push_back(v_index);
				object_parse_data.vt_indices.push_back(vt_index);
				object_parse_data.vn_indices.push_back(vn_index);
			}
		}
	}

	// make the data usable by OpenGL element array buffer
	correctify();
}

/* The OBJ file has lines such as "f 0/1/2 ...", where the indices are not equal.
We would like something like "f 0/0/0 ...", which is what this method accomplishes via
the use of C++ maps. */
void OBJObject::correctify() {
	using std::vector;
	std::multimap<vector<float>, vector<vector<float>>> v_to_vtvn;
	std::map<vector<vector<float>>, size_t> vert_to_index;
	vector<size_t>::size_type v_sz = object_parse_data.v_indices.size();
	vector<size_t>::size_type vt_sz = object_parse_data.vt_indices.size();
	vector<size_t>::size_type vn_sz = object_parse_data.vn_indices.size();

	if (v_sz != vt_sz || v_sz != vn_sz || vt_sz != vn_sz) {
		std::cerr << "Error: The number of indices for verts, texcoords, and normals "
			<< "do not match." << std::endl;
	}

	size_t element_index = 0;
	for (vector<size_t>::size_type i = 0; i < v_sz; ++i) {
		int v_index = 3 * object_parse_data.v_indices[i];
		int vt_index = 2 * object_parse_data.vt_indices[i];
		int vn_index = 3 * object_parse_data.vn_indices[i];

		vector<float> v_data;
		v_data.push_back(object_parse_data.vertices[v_index]);
		v_data.push_back(object_parse_data.vertices[v_index + 1]);
		v_data.push_back(object_parse_data.vertices[v_index + 2]);
		vector<float> vt_data;
		vt_data.push_back(object_parse_data.texcoords[vt_index]);
		vt_data.push_back(object_parse_data.texcoords[vt_index + 1]);
		vector<float> vn_data;
		vn_data.push_back(object_parse_data.normals[vn_index]);
		vn_data.push_back(object_parse_data.normals[vn_index + 1]);
		vn_data.push_back(object_parse_data.normals[vn_index + 2]);

		vector<vector<float>> vt_vn_data;
		vt_vn_data.push_back(vt_data);
		vt_vn_data.push_back(vn_data);
		vector<vector<float>> v_vt_vn_data;
		v_vt_vn_data.push_back(v_data);
		v_vt_vn_data.push_back(vt_data);
		v_vt_vn_data.push_back(vn_data);

		typedef std::multimap<vector<float>, vector<vector<float>>> mmap_vf_vvf;
		std::pair<mmap_vf_vvf::iterator, mmap_vf_vvf::iterator> results = v_to_vtvn.equal_range(v_data);

		if (results.first != results.second) {
			bool match_found = false;
			while (results.first != results.second) {
				std::pair<vector<float>, vector<vector<float>>> a_result = *(results.first);
				vector<float>& tex = a_result.second[0];
				vector<float>& norm = a_result.second[1];

				if (tex[0] == vt_data[0] && tex[1] == vt_data[1] && norm[0] == vn_data[0]
					&& norm[1] == vn_data[1] && norm[2] == vn_data[2]) {

					size_t index = vert_to_index[v_vt_vn_data];
					indices.push_back(index);
					match_found = true;
					break;
				}

				++results.first;
			}

			if (match_found) {
				continue;
			}
		}

		v_to_vtvn.insert(std::pair<vector<float>, vector<vector<float>>>(v_data, vt_vn_data));
		vert_to_index.insert(std::pair<vector<vector<float>>, size_t>(v_vt_vn_data, element_index));
		vertices.insert(vertices.end(), v_data.begin(), v_data.end());
		texcoords.insert(texcoords.end(), vt_data.begin(), vt_data.end());
		normals.insert(normals.end(), vn_data.begin(), vn_data.end());
		indices.push_back(element_index);

		++element_index;
	}
}