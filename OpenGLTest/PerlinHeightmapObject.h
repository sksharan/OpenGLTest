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
		                 float shininess, GLuint program_object, glm::vec3 start_pos, int length, float spacing, float amplitude);

	/* Get all the PerlinHeightmapObjects created */
	static std::vector<PerlinHeightmapObject*>& getPerlinHeightmapObjects();

	/* Given an (X, Z) coordinate in world space, returns the height of this heightmap at that location. */
	float getY(float x_world_pos, float y_world_pos);

	void render();

private:
	/* The Perlin noise module. */
	noise::module::Perlin perlin_module;

	/* So that this heightmap can use multiple textures.  */
	GLuint texture1, texture2, texture3, texture4;

	/* Returns the height using a Perlin noise equation. */
	virtual float getY(int x, int z);

	/* Adds texcoords given a vertex at (X, Z). Coordinates work as described in the comment for HeightmapObject::getY() */
	virtual void addTexcoords(int x, int z);

	/* Initialize the texture for use with this object. */
	virtual void initTexture();

	/* All PerlinHeightmapObjects created. */
	static std::vector<PerlinHeightmapObject*> perlinHeightmapObjects;
};

#endif