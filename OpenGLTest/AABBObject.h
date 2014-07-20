#ifndef AABBOBJECT_H
#define AABBOBJECT_H

#include "RenderableObject.h"
#include <vector>

/* Class representing an Axis-Aligned Bounding Box. */
class AABBObject : public RenderableObject {
public:
	/* Creates an AABB around 'obj.' */
	AABBObject(RenderableObject* obj);

	/* Calulates the vertices, texcoords, normals, and indices of the AABB. Should be called whenever the object
	that this AABB contains is transformed. */
	void calculateAABB();

	/* Calling this function has no effect, as AABB's move with the object that they surround. */
	virtual void setModelMatrix(glm::mat4 newModelMatrix);

	/* Renders this object with GL_LINES as the drawing mode. */
	void render();

	/* Returns reference to all AABBObjects that have been created. */
	static std::vector<AABBObject*>& getAABBObjects();

private:
	/* The object that this AABB surrounds. */
	RenderableObject* object;

	/* A vector of all AABBObjects that have been instantiated so far. */
	static std::vector<AABBObject*> aabbObjects;
};

#endif