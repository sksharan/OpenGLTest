#include "PerlinHeightmapObject.h"
#include "noiseutils/noiseutils.h"
#include <SOIL.h>

std::vector<PerlinHeightmapObject*> PerlinHeightmapObject::perlinHeightmapObjects;

void PerlinHeightmapObject::render() {
	glUseProgram(program);
	setUniforms();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glActiveTexture(GL_TEXTURE0 + 4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

PerlinHeightmapObject::PerlinHeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	float shininess, GLuint program_object, glm::vec3 start_pos, int length, float spacing, float amplitude) {

	initRenderableObjectStart(name, isVisible, lighting_enabled, ambient, diffuse, specular, shininess, program_object);

	texture_filename = "unused -- the multiple textures are defined in the initTexture() method";
	heightmap_filename = "unused";
	start_position = start_pos;
	heightmap_length = length;
	heightmap_spacing = spacing;
	heightmap_amplitude = amplitude;

	//modify properties of the perlin module as needed
	perlin_module.SetOctaveCount(6);
	perlin_module.SetFrequency(1.0);
	perlin_module.SetPersistence(0.5);

	generateHeightmap();  //initializes vertices, texcoords, normals, indices

	perlinHeightmapObjects.push_back(this);
	initRenderableObjectEnd();
}

std::vector<PerlinHeightmapObject*>& PerlinHeightmapObject::getPerlinHeightmapObjects() {
	return perlinHeightmapObjects;
}

float PerlinHeightmapObject::getY(float x_world_pos, float z_world_pos) {
	return getY(int((x_world_pos - start_position.x) / heightmap_spacing), int(-(z_world_pos - start_position.z) / heightmap_spacing));
}

float PerlinHeightmapObject::getY(int x, int z) {
	double px = ((float)x * heightmap_spacing + start_position.x) / heightmap_amplitude * 0.15;
	double pz = ((float)z * heightmap_spacing - start_position.z) / heightmap_amplitude * 0.15;
	double value = perlin_module.GetValue(px, 1, pz);
	return heightmap_amplitude * value;
}

void PerlinHeightmapObject::addTexcoords(int x, int z) {
	float u, v;
	float repeat_factor = 16.0f;
	u = (float)x / repeat_factor;
	v = (float)z / repeat_factor;
	texcoords.push_back(u);
	texcoords.push_back(v);
}

void PerlinHeightmapObject::initTexture() {
	int img_width, img_height;
	unsigned char* img_data;

	glActiveTexture(GL_TEXTURE0 + 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	img_data = SOIL_load_image("textures/landscape/grass1.jpg", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(img_data);

	glActiveTexture(GL_TEXTURE0 + 1);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	img_data = SOIL_load_image("textures/landscape/grass2.jpg", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(img_data);

	glActiveTexture(GL_TEXTURE0 + 2);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	img_data = SOIL_load_image("textures/landscape/rock1.jpg", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(img_data);

	glActiveTexture(GL_TEXTURE0 + 3);
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	img_data = SOIL_load_image("textures/landscape/dirt1.jpg", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(img_data);

	glActiveTexture(GL_TEXTURE0 + 4);
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	img_data = SOIL_load_image("textures/landscape/plant_alpha.png", &img_width, &img_height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	SOIL_free_image_data(img_data);
}