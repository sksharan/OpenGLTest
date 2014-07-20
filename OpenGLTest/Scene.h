#ifndef SCENE_H
#define SCENE_H

#include "RenderableObject.h"
#include "AABBObject.h"
#include "OBBObject.h"
#include <vector>


/* Class representing a scene with objects in it that can be manipulated. */
class Scene {
public:
	/* Creates a new scene with the designated 'clearing_color' and 'clearing_depth' (used by glClearColr() and glClearDepth()). */
	Scene(glm::vec4 clearing_color, float clearing_depth);

	/* Returns reference to all the objects in this scene that are to be rendered. */
	const std::vector<RenderableObject*>& getSceneObjects();

	/* Add 'object' to this scene. The first object added becomes the current object in the scene. The AABB and OBB for the object is
	created and added to the scene. */
	void addObject(RenderableObject* object);

	/* Returns reference to all AABB's in this scene. */
	const std::vector<AABBObject*>& getAABBObjects();

	/* Returns reference to all OBB's in this scene. */
	const std::vector<OBBObject*>& getOBBObjects();

	/* Returns the clear color.*/
	glm::vec4 getClearColor();

	/* Returns the clear depth. */
	float getClearDepth();

	/* Returns pointer to the currently selected object. Returns NULL if no objects are in the scene. */
	RenderableObject* getCurrObject();

	/* Returns pointer to the AABB of the current object, or NULL if no objects are in the scene. */
	AABBObject* getCurrAABB();

	/* Returns pointer to the OBB of the current object, or NULL if no objects are in the scene. */
	OBBObject* getCurrOBB();

	/* Changes the currently selected object to the next one in the list (will wrap around to the start of the list when
	the end of the list is reached). */
	void changeToNextObject();

	/* Changes the currently selected object to the previous one in the list (will wrap around to the end of the list when
	the start of the list is reached). */
	void changeToPrevObject();

private:
	/* Pointers to the objects in this scene that are to be rendered. Implementation note: each object is followed by its
	corresponding AABBObject and OBBOBject in the list. */
	std::vector<RenderableObject*> scene_objects;

	/* Pointer to the currently selected object. */
	RenderableObject* curr_object;

	/* Pointers to all AABB's in this scene. */
	std::vector<AABBObject*> aabb_objects;

	/* Pointers to all OBB's in this scene. */
	std::vector<OBBObject*> obb_objects;

	/* 'curr_object' is in scene_objects[objectIndex]. */
	unsigned int objectIndex;

	/* The clear color (background color) for this scene (used by glClearColor()). */
	glm::vec4 clear_color;

	/* The clear depth for this scene (used by glClearDepth()). */
	float clear_depth;
};

#endif