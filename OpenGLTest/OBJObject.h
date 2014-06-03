#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include "RenderableObject.h"
#include <vector>
#include <string>

/* An object whose data comes from a Wavefront OBJ file. */
class OBJObject : public RenderableObject {

public:
	/* name: name of this object
	isVisible: true iff this object is visible
	lighting_enabled: true iff lighting calculations should affect this object
	ambient: ambient term of this object
	diffuse: diffuse term of this object
	specular: specular term of this object
	shininess: shininess term of this object
	tex_filename: filename of the texture associated with this object
	obj_filename: filename of the Wavefront OBJ associated with this object
	*/
	OBJObject(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
		      float shininess, std::string tex_filename, std::string obj_filename);

	/* Write the corrected OBJ data to the specified file. */
	void writeOBJ(std::string filename);

private:
	/* The filename of the Wavefront OBJ associated with this object */
	std::string obj_file;

	/* The filename of the 'corrected' Wavefront OBJ associated with this object. The indexing of the original file
	* has to be modified because of the way OpenGL does indexed drawing. */
	std::string corrected_obj_file;

	/* Parses the OBJ and loads the data into 'vertices', 'normals', 'texcoords', and 'indices' */
	void parseOBJ();

	/* Corrects the OBJ data to be OpenGL-compatible. */
	void correctify();

	/* A private struct used in parsing and correcting the input OBJ file. */
	struct OBJParseData {
		std::vector<float> vertices, texcoords, normals;
		std::vector<size_t> v_indices, vt_indices, vn_indices;
	} object_parse_data;
};

#endif