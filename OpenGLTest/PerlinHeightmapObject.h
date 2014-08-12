#ifndef PERLINHEIGHTMAPOBJECT_H
#define PERLINHEIGHTMAPOBJECT_H

#include "HeightmapObject.h"
#include <noise/noise.h>

/* A HeightmapObject whose height values a determined by a Perlin noise equation. */
class PerlinHeightmapObject : public HeightmapObject {
public:
	/* Similar to constructor for HeightmapObject, but excludes argument for texture filename (the texture is generated internally) and argument
	for heightmap filename.  */
	PerlinHeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
		                 float shininess, glm::vec3 start_pos, int length, float spacing, float amplitude);

	/* Get all the PerlinHeightmapObjects created */
	static std::vector<PerlinHeightmapObject*>& getPerlinHeightmapObjects();

private:
	/* The Perlin noise module. */
	noise::module::Perlin perlin_module;

	/* Returns the height using a Perlin noise equation. */
	virtual float getY(int x, int z);

	/* Generate the texture for this object. */
	void genTexture();

	/* All PerlinHeightmapObjects created. */
	static std::vector<PerlinHeightmapObject*> perlinHeightmapObjects;
};

#endif