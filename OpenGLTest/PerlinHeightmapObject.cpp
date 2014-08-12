#include "PerlinHeightmapObject.h"
#include "noiseutils/noiseutils.h"
#include <SOIL.h>

std::vector<PerlinHeightmapObject*> PerlinHeightmapObject::perlinHeightmapObjects;

PerlinHeightmapObject::PerlinHeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	                                         float shininess, glm::vec3 start_pos, int length, float spacing, float amplitude) {

	initRenderableObjectStart(name, isVisible, lighting_enabled, ambient, diffuse, specular, shininess);

	texture_filename = "textures/perlin/" + std::to_string(start_pos.x) + " " + std::to_string(start_pos.y) + " " + std::to_string(start_pos.z) + ".bmp";

	heightmap_filename = "unused";
	start_position = start_pos;
	heightmap_length = length;
	heightmap_spacing = spacing;
	heightmap_amplitude = amplitude;

	//modify properties of the perlin module as needed
	perlin_module.SetOctaveCount(6);
	perlin_module.SetFrequency(1.0);
	perlin_module.SetPersistence(0.5);

	genTexture();
	generateHeightmap();  //initializes vertices, texcoords, normals, indices

	perlinHeightmapObjects.push_back(this);
	initRenderableObjectEnd();
}

std::vector<PerlinHeightmapObject*>& PerlinHeightmapObject::getPerlinHeightmapObjects() {
	return perlinHeightmapObjects;
}

float PerlinHeightmapObject::getY(int x, int z) {
	double px = (x + start_position.x) / heightmap_amplitude * 0.15;
	double pz = -((z + start_position.z) / heightmap_amplitude * 0.15);
	double value = perlin_module.GetValue(px, 0, pz);
	return heightmap_amplitude * value;
}

/* Some code adapted from http://libnoise.sourceforge.net/tutorials/tutorial3.html */
void PerlinHeightmapObject::genTexture() {
	utils::NoiseMap noise_map;
	utils::NoiseMapBuilderPlane noise_map_builder;
	noise_map_builder.SetSourceModule(perlin_module);
	noise_map_builder.SetDestNoiseMap(noise_map);
	noise_map_builder.SetDestSize(heightmap_length, heightmap_length);
	float lower_x = (0 + start_position.x) / heightmap_amplitude * 0.15;
	float upper_x = (heightmap_length - 1 + start_position.x) / heightmap_amplitude * 0.15;
	float lower_z = -((heightmap_length - 1 + start_position.z) / heightmap_amplitude * 0.15);
	float upper_z = -((0 + start_position.z) / heightmap_amplitude * 0.15);
	noise_map_builder.SetBounds(lower_x, upper_x, lower_z, upper_z);
	noise_map_builder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(noise_map);
	renderer.SetDestImage(image);
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.00, utils::Color(154, 205, 50, 255));
	renderer.AddGradientPoint(-0.75, utils::Color(40, 188, 40, 255));
	renderer.AddGradientPoint(-0.50, utils::Color(0, 128, 64, 255));
	renderer.AddGradientPoint(-0.25, utils::Color(154, 205, 50, 255));
	renderer.AddGradientPoint(0.00, utils::Color(0, 128, 64, 255));
	renderer.AddGradientPoint(0.25, utils::Color(40, 188, 40, 255));
	renderer.AddGradientPoint(0.50, utils::Color(154, 205, 50, 255));
	renderer.AddGradientPoint(0.75, utils::Color(20, 148, 20, 255));
	renderer.AddGradientPoint(0.90, utils::Color(154, 205, 50, 255));
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename(texture_filename);
	writer.WriteDestFile();
}