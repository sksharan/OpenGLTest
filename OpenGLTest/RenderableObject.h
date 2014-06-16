/* Defines a general class for any object that can be rendered. */

#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

/* Class which represents any object that can be rendered to the screen. */
class RenderableObject {

public:
	/* A vector of all the RenderableObjects that have been instantiated so far. */
	static std::vector<RenderableObject*> renderableObjects;

	/* name: name of this object
	   v: vertices of this object
	   t: texture coordinates of this object
	   n: normals of this object
	   i: indices of this object
	   isVisible: true iff this object is visible
	   lighting_enabled: true iff lighting calculations should affect this object
	   ambient: ambient term of this object
	   diffuse: diffuse term of this object
	   specular: specular term of this object
	   shininess: shininess term of this object
	   tex_filename: filename of the texture associated with this object
	*/
	RenderableObject(std::string name, std::vector<float> v, std::vector<float> t, std::vector<float> n, std::vector<GLuint> i, bool isVisible,
		             bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess, std::string tex_filename);

	~RenderableObject();

	/* Render this object to the screen. */
	virtual void render();

	/* Returns the name of this object. */
	std::string getName();

	/* Returns a const reference to the list of vertices. */
	const std::vector<float>& getVertices();

	/* Returns a const reference to the list of texcoords. */
	const std::vector<float>& getTexcoords();

	/* Returns a const reference to the list of normals. */
	const std::vector<float>& getNormals();

	/* Returns a const reference to the list of indices. */
	const std::vector<GLuint>& getIndices();

	/* Returns true iff this object is visible and should be rendered to the screen. */
	bool isVisible();

	/* Toggles visibility of this object on/off. */
	void toggleVisibilty();


protected:
	/* A constructor that does nothing. */
	RenderableObject();

	/* Sets up the vertex array object. Called in the constructor. */
	virtual void initVao();

	/* Initialize the texture for use with this object. */
	virtual void initTexture();

	/* Name of this object. */
	std::string objectName;

	/* The vertices of the object (3 elements per vertex). */
	std::vector<float> vertices;

	/* The texture coordinates of the object (2 elements per texture coordinate). */
	std::vector<float> texcoords;

	/* The normals of the object (3 elements per normal) */
	std::vector<float> normals;

	/* Indices used to do indexed rendering. */
	std::vector<GLuint> indices;

	/* True iff this object is visible and should be rendered to the screen. */
	bool visible;

	/* True iff lighting calculations affect this object. */
	bool light_enabled;

	/* The ambient term for this object. */
	glm::vec4 ambient_term;
	
	/* The diffuse term for this object. */
	glm::vec4 diffuse_term;

	/* The specular term for this object. */
	glm::vec4 specular_term;

	/* The shininess of this object. */
	float shininess_term;

	/* Filename of the texture for this object. */
	std::string texture_filename;

	/* The vertex buffer object for vertices. */
	GLuint vbo_vertices;

	/* The vertex buffer object for texture coordinates. */
	GLuint vbo_texcoords;

	/* The vertex buffer object for normals. */
	GLuint vbo_normals;

	/* The vertex buffer object for indices. */
	GLuint vbo_indices;

	/* Represents the texture for this object. */
	GLuint texture;

	/* Vertex array object associated with this RenderableObject. */
	GLuint vao;
};

#endif