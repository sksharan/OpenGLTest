#ifndef AABBOBJECT_H
#define AABBOBJECT_H

#include "RenderableObject.h"
#include "Ray.h"
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

	/* Returns the minimum corner of this box. */
	glm::vec3 getMinCorner();

	/* Returns the maximum corner of this box. */
	glm::vec3 getMaxCorner();

	/* Returns true iff 'ray' intersects this box. When true, returns the t value at which the ray intersects the box
	(the ray equation is r(t) = origin + t * direction). */
	bool rayIntersects(Ray& ray, int& t);

	/* Returns reference to all AABBObjects that have been created. */
	static std::vector<AABBObject*>& getAABBObjects();

private:
	/* The object that this AABB surrounds. */
	RenderableObject* object;

	/* The minimum corner of this box. */
	glm::vec3 min_extent;

	/* The maximum corner of this box. */
	glm::vec3 max_extent;

	/* A vector of all AABBObjects that have been instantiated so far. */
	static std::vector<AABBObject*> aabbObjects;
};

#endif