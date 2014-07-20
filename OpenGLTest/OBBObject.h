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

	/* Calling this function has no effect, as OBB's move with the object that they surround. */
	virtual void setModelMatrix(glm::mat4 newModelMatrix);

	/* Renders this object with GL_LINES as the drawing mode. */
	void render();

	/* Returns all OBBObjects that have been created. */
	static std::vector<OBBObject*>& getOBBObjects();

private:
	/* The object that this OBB surrounds. */
	RenderableObject* object;

	/* A vector of all OBBObjects that have been instantiated so far. */
	static std::vector<OBBObject*> obbObjects;
};

#endif