#include "HeightmapObject.h"
#include <SOIL.h>

void HeightmapObject::render() {
	setUniforms();
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

HeightmapObject::HeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	                             float shininess, std::string tex_filename, std::string hm_filename, glm::vec3 start_pos, int length, float spacing, float amplitude) {

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
	heightmap_spacing = spacing;
	heightmap_amplitude = amplitude;
	renderMode = RENDERMODE_TEXTURED;
	modelMatrix = glm::mat4();
	programState.modelMatrix = modelMatrix;
	aabb = NULL;

	int img_width, img_height;
	heightmap_pixels = SOIL_load_image(heightmap_filename.c_str(), &img_width, &img_height, 0, SOIL_LOAD_RGBA); //load the pixels

	generateHeightmap();  //initializes vertices, texcoords, normals, indices

	initVao();
	initTexture();

	renderableObjects.push_back(this);
}

/* Implementation partially adapted from  http://www.learnopengles.com/android-lesson-eight-an-introduction-to-index-buffer-objects-ibos/ . */
void HeightmapObject::generateHeightmap() {
	glm::vec3 position = start_position;

	for (int z = 0; z < heightmap_length; z++, position += glm::vec3(0, 0, -heightmap_spacing)) {

		position.x = start_position.x;

		for (int x = 0; x < heightmap_length; x++, position += glm::vec3(heightmap_spacing, 0, 0)) {
			//add vertex
			vertices.push_back(position.x);
			vertices.push_back(getY(x, z));
			vertices.push_back(position.z);

			//add texcoord
			float u = 1 / float(heightmap_length) * x;
			float v = 1 / float(heightmap_length) * z;
			texcoords.push_back(u);
			texcoords.push_back(v);

			//add normal (FIXME later)
			addNormals(x, z);
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

/* Remember that we need to treat colors on a 0 to 1 scale. */
float HeightmapObject::getY(int x, int z) {
	int index = (x + z * heightmap_length) * HM_TEXTURE_NUM_CHANNELS;
	float red_value = (float)heightmap_pixels[index] * heightmap_amplitude / 255.0f;
	float blue_value = (float)heightmap_pixels[index + 1] * heightmap_amplitude / 255.0f;
	float green_value = (float)heightmap_pixels[index + 2] * heightmap_amplitude / 255.0f;
	return red_value;
}


void HeightmapObject::addNormals(int x, int z) {
	/* The vector representing the normal. */
	glm::vec3 normal = glm::vec3(0, 1, 0);

	//FIXME

	normals.push_back(normal.x);
	normals.push_back(normal.y);
	normals.push_back(normal.z);
}