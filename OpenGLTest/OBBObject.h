#ifndef OBBOBJECT_H
#define OBBOBJECT_H

#include "RenderableObject.h"

/* Class representing an Oriented Bounding Box. */
class OBBObject : public RenderableObject {
public:
	/* Creates an OBB around 'obj.' */
	OBBObject(RenderableObject* obj);

	/* Calulates the vertices, texcoords, normals, and indices of the OBB. Should be called whenever the object
	that this OBB contains is transformed. */
	void calculateOBB();

private:
	/* The object that this OBB surrounds. */
	RenderableObject* object;

	/* A vector of all OBBObjects that have been instantiated so far. */
	static std::vector<OBBObject*> obbObjects;
};

#endif