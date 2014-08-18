#ifndef OBBOBJECT_H
#define OBBOBJECT_H

#include "RenderableObject.h"
#include "Ray.h"

/* Class representing an Oriented Bounding Box. */
class OBBObject : public RenderableObject {
public:
	/* Creates an OBB around 'obj.' */
	OBBObject(RenderableObject* obj, GLuint program_object);

	/* Calulates the vertices, texcoords, normals, and indices of the OBB. Should be called whenever the object
	that this OBB contains is transformed. */
	void calculateOBB();

	/* Calling this function has no effect, as OBB's move with the object that they surround. */
	virtual void setModelMatrix(glm::mat4 newModelMatrix);

	/* Renders this object with GL_LINES as the drawing mode. */
	void render();

	/* Returns the minimum corner of this box. */
	glm::vec3 getMinCorner();

	/* Returns the maximum corner of this box. */
	glm::vec3 getMaxCorner();

	/* Returns true iff 'ray' intersects this box. */
	bool rayIntersects(Ray& ray);

	/* Returns all OBBObjects that have been created. */
	static std::vector<OBBObject*>& getOBBObjects();

private:
	/* The object that this OBB surrounds. */
	RenderableObject* object;

	/* The minimum corner of this box. */
	glm::vec3 min_extent;

	/* The maximum corner of this box. */
	glm::vec3 max_extent;

	/* A vector of all OBBObjects that have been instantiated so far. */
	static std::vector<OBBObject*> obbObjects;
};

#endif