/* Class representing a grid-based object that extends in the x and z
direction. The height values along the y-axis are dtermined from images ("heightmaps"). */

#ifndef HEIGHTMAPOBJECT_H
#define HEIGHTMAPOBJECT_H

#include "RenderableObject.h"
#include <glm/glm.hpp>

/* All images are converted to 32-bit by SOIL. We use this constant in determining the height value at
a given point - see the method getY(). */
#define HM_TEXTURE_BIT_DEPTH 32

/* The number of channels. 4 means were are using the red, green, blue, and alpha channels. */
#define HM_TEXTURE_NUM_CHANNELS 4

class HeightmapObject : public RenderableObject {
public:
	/* name: name of this object
	v: vertices of this object
	isVisible: true iff this object is visible
	lighting_enabled: true iff lighting calculations should affect this object
	ambient: ambient term of this object
	diffuse: diffuse term of this object
	specular: specular term of this object
	shininess: shininess term of this object
	tex_filename: filename of the texture associated with this object
	hm_filename: the name of the heightmap associated wit this object; must be length x length pixels (see below)
	start_pos: position that generation of the heightmap will begin at. Heightmap grows in the positive x and
	           negative z directions
    length: the generated heightmap will be length x length vertices in dimension
	spacing: spacing between vertices
	amplitude: affects the height values of the generated mesh
	*/
	HeightmapObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
	                float shininess, std::string tex_filename, std::string hm_filename, glm::vec3 start_pos, int length, float spacing, float amplitude);

private:

	/* Uses GL_TRIANGLE_STRIP for rendering. */
	virtual void render();

	/* Get the height value at a given position (x, z). We use this coordinate to represent the vertices rather than the world position,
	so (0, 0) is the start position and (heightmap_length - 1, heightmap_length - 1) is the end position of the heightmap. The returned value
	is in terms of world coordinates. */
	float getY(int x, int z);

	/* Generates the heightmap and adds the data to 'vertices, 'texcoords, 'normals', and 'indices'. */
	void generateHeightmap();

	/* Adds normals given a vertex at (X, Z). Coordinates work as described in the comment for getY() */
	void addNormals(int x, int z);

	/* Name of the heightmap that will determine height values for this object. */
	std::string heightmap_filename;

	/* Generation of the heightmap starts at this position and extends in the positive x and negative z directions. */
	glm::vec3 start_position;

	/* The heightmap is length x length vertices. */
	int heightmap_length;

	/* Distance between vertices. */
	float heightmap_spacing;

	/* Affects the height values of the generated mesh. */
	float heightmap_amplitude;

	/* The pixels that make up the heightmap image (the one used to determine height values, not the texture
	applied to the object. */
	unsigned char* heightmap_pixels;
};

#endif