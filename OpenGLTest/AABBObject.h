#ifndef AABBOBJECT_H
#define AABBOBJECT_H

#include "RenderableObject.h"
#include <vector>

/* Class representing an Axis-Aligned Bounding Box. */
class AABBObject : public RenderableObject {
public:
	/* Creates an AABB around 'object.' */
	AABBObject(RenderableObject* obj);

	/* Calulates the vertices, texcoords, normals, and indices of the AABB. Should be called whenever the object
	that this AABB contains is transformed. */
	void calculateAABB();

private:
	/* The object that this AABB surrounds. */
	RenderableObject* object;

	/* A vector of all AABBObjects that have been instantiated so far. */
	static std::vector<AABBObject*> aabbObjects;
};

#endif