#include "HeightmapObject.h"

void HeightmapObject::render() {
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

HeightmapObject::HeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	                             float shininess, std::string tex_filename, std::string hm_filename, glm::vec3 start_pos, int length, float stride) {

	objectName = name;
	visible = isVisible;
	light_enabled = lighting_enabled;
	ambient_term = ambient;
	diffuse_term = diffuse;
	specular_term = specular;
	shininess_term = shininess;
	texture_filename = tex_filename;
	heightmap_filename = hm_filename;
	start_position = start_pos;
	heightmap_length = length;
	heightmap_stride = stride;

	generateHeightmap();  //initializes vertices, texcoords, normals, indices

	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

/* Implementation partially adapted from  http://www.learnopengles.com/android-lesson-eight-an-introduction-to-index-buffer-objects-ibos/ . */
void HeightmapObject::generateHeightmap() {
	glm::vec3 position = start_position;

	for (int z = 0; z < heightmap_length; z++, position += glm::vec3(0, 0, -heightmap_stride)) {

		position.x = start_position.x;

		for (int x = 0; x < heightmap_length; x++, position += glm::vec3(heightmap_stride, 0, 0)) {
			//add vertex
			vertices.push_back(position.x);
			vertices.push_back(position.y); // FIXME later
			vertices.push_back(position.z);

			//add texcoord
			float u = 1 / float(heightmap_length) * x;
			float v = 1 / float(heightmap_length) * z;
			texcoords.push_back(u);
			texcoords.push_back(v);

			//add normal (FIXME later)
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
		}
	}

	//generate indices
	for (int z = 0; z < heightmap_length - 1; z++) {
		// repeat the first index if a degenerate triangle is needed
		if (z > 0) {
			indices.push_back(GLuint(z * heightmap_length));
		}

		for (int x = 0; x < heightmap_length; x++) {
			indices.push_back(GLuint(x + z * heightmap_length));
			indices.push_back(GLuint(x + (z + 1) * heightmap_length));
		}

		//repeat the last index if a degenerate triangle is needed
		if (z < heightmap_length - 2) {
		    indices.push_back(GLuint((heightmap_length - 1) + ((z + 1) * heightmap_length)));
		}
	}
}