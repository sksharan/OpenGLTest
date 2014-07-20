/* Defines a general class for any object that can be rendered. */

#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "EnumRenderMode.h"
#include "ProgramState.h"

/* Class which represents any object that can be rendered to the screen. */
class RenderableObject {

public:

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
	RenderableObject(std::string name, std::vector<float>& v, std::vector<float>& t, std::vector<float>& n, std::vector<GLuint>& i, bool isVisible,
		             bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess, std::string tex_filename);

	~RenderableObject();

	/* Render this object to the screen. */
	virtual void render();

	/* Returns a const reference to a vector of all RenderableObjects created. */
	static const std::vector<RenderableObject*>& getRenderableObjects();

	/* Returns the name of this object. */
	std::string getName();

	/* Returns a const reference to the list of vertices. */
	const std::vector<float>& getVertices();

	/* Sets the vertices of this object to 'newVertices.'*/
	void setVertices(std::vector<float>& newVertices);

	/* Returns a const reference to the list of texcoords. */
	const std::vector<float>& getTexcoords();

	/* Sets the texcoords of this object to 'newTexcoords.' */
	void setTexcoords(std::vector<float>& newTexcoords);

	/* Returns a const reference to the list of normals. */
	const std::vector<float>& getNormals();

	/* Sets the normals of this object to 'newNormals.' */
	void setNormals(std::vector<float>& newNormals);

	/* Returns a const reference to the list of indices. */
	const std::vector<GLuint>& getIndices();

	/* Sets the indices of this object to 'newIndices.' */
	void setIndices(std::vector<GLuint>& newIndices);

	/* Returns true iff this object is visible and should be rendered to the screen. */
	bool isVisible();

	/* Toggles visibility of this object on/off. */
	void toggleVisibilty();

	/* Returns true iff this object is influenced by lighting calculations. */
	bool getLightEnabledStatus();

	/* Toggle whether or not this object is influenced by lighting calculations. */
	void toggleLightEnabledStatus();

	/* Returns the render mode of this object. */
	RenderMode getRenderMode();

	/* Sets the render mode of this object to 'mode'. */
	void setRenderMode(RenderMode mode);

	/* Returns the model matrix of this object. */
	glm::mat4 getModelMatrix();

	/* Set the new model matrix of this object to 'newModelMatrix.' Updates the AABB if one is enabled for
	this object. */
	virtual void setModelMatrix(glm::mat4 newModelMatrix);

protected:
	/* A constructor that does nothing. */
	RenderableObject();

	/* Children of RenderableObject may call this method at the start of their constructors. This handles initialization of all
	RenderableObject fields except 'vertices', 'texcoords', 'normals', and 'indices', which must be handled by the child class. */
	void initRenderableObjectStart(std::string name, bool isVisible, bool lighting_enabled, glm::vec4 ambient, glm::vec4 diffuse,
		                           glm::vec4 specular, float shininess, std::string tex_filename);

	/* Children of RenderableObject may call this method at the end of their constructors. This handles the creation of VAOs and VBOs,
	and binds the texture. */
	void initRenderableObjectEnd();

	/* Sets up the vertex array object. Called in the constructor. Will also initialize the vertex buffer objects. */
	virtual void initVao();

	/* Initializes the vertex buffer object for vertices. */
	void initVboVertices();

	/* Initializes the vertex buffer object for texcoords. */
	void initVboTexcoords();

	/* Initializes the vertex buffer object for normals. */
	void initVboNormals();

	/* Initializes the vertex buffer object for indices. */
	void initVboIndices();

	/* Initialize the texture for use with this object. */
	void initTexture();

	/* Set up the uniforms for this object. */
	void setUniforms();

	/* Update the ambient uniform for this object. */
	void updateAmbientUniform();

	/* Update the diffuse uniform for this object. */
	void updateDiffuseUniform();

	/* Update the specular uniform for this object. */
	void updateSpecularUniform();

	/* Update the shininess uniform for this object. */
	void updateShininessUniform();

	/* Update the light-enabled uniform for this object. */
	void updateLightEnabledUniform();

	/* Update the render mode uniform of this object.*/
	void updateRenderModeUniform();

	/* A vector of all the RenderableObjects that have been instantiated so far (does not include children of RenderableObject). */
	static std::vector<RenderableObject*> renderableObjects;

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

	/* The type of rendering to use with this object. */
	RenderMode renderMode;

	/* The model matrix of this object. */
	glm::mat4 modelMatrix;
};

#endif