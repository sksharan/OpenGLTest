#include "Scene.h"

Scene::Scene(std::string scene_name, glm::vec4 clearing_color, float clearing_depth) {
	name = scene_name;
	clear_color = clearing_color;
	clear_depth = clearing_depth;
	curr_object = NULL;
	objectIndex = 0;
}

const std::vector<RenderableObject*>& Scene::getSceneObjects() {
	return scene_objects;
}

void Scene::addObject(RenderableObject* object) {
	scene_objects.push_back(object);

	//if this is the first object we added, make this object the current current object
	if (scene_objects.size() == 1) {
		curr_object = object;
		printf("%s now selected in scene %s\n", curr_object->getName().c_str(), name.c_str());
	}

	AABBObject* aabb_object = new AABBObject(object);
	scene_objects.push_back(aabb_object); //we'll render the AABB to the screen
	aabb_objects.push_back(aabb_object);

	OBBObject* obb_object = new OBBObject(object);
	scene_objects.push_back(obb_object); //we'll render the OBB to the screen
	obb_objects.push_back(obb_object);
}

const std::vector<AABBObject*>& Scene::getAABBObjects() {
	return aabb_objects;
}

const std::vector<OBBObject*>& Scene::getOBBObjects() {
	return obb_objects;
}

glm::vec4 Scene::getClearColor() {
	return clear_color;
}

float Scene::getClearDepth() {
	return clear_depth;
}

RenderableObject* Scene::getCurrObject() {
	return curr_object;
}

AABBObject* Scene::getCurrAABB() {
	// Do nothing if there are no objects to work with
	if (scene_objects.size() == 0) {
		return NULL;
	}

	return (AABBObject*)scene_objects[objectIndex + 1];
}

OBBObject* Scene::getCurrOBB() {
	// Do nothing if there are no objects to work with
	if (scene_objects.size() == 0) {
		return NULL;
	}

	return (OBBObject*)scene_objects[objectIndex + 2];
}

void Scene::changeToNextObject() {
	// Do nothing if there are no objects to work with
	if (scene_objects.size() == 0) {
		return;
	}

	if (objectIndex == scene_objects.size() - 3) {
		objectIndex = 0;
	}
	else {
		objectIndex+=3; //skip the AABB and OBB
	}

	curr_object = scene_objects[objectIndex];
	printf("%s now selected in scene %s\n", curr_object->getName().c_str(), name.c_str());
}

void Scene::changeToPrevObject() {
	// Do nothing if there are no objects to work with
	if (scene_objects.size() == 0) {
		return;
	}

	if (objectIndex == 0) {
		objectIndex = scene_objects.size() - 3;
	}
	else {
		objectIndex-=3; //skip the AABB and OBB
	}

	curr_object = scene_objects[objectIndex];
	printf("%s now selected in scene %s\n", curr_object->getName().c_str(), name.c_str());
}

void Scene::setCurrObjectWithOBBIndex(int obb_index) {
	if (obb_index < 0 || obb_index >= getOBBObjects().size()) {
		return;
	}

	curr_object = scene_objects[obb_index * 3];
	printf("%s now selected in scene %s\n", curr_object->getName().c_str(), name.c_str());
}

void Scene::setCurrObjectWithAABBIndex(int aabb_index) {
	if (aabb_index < 0 || aabb_index >= getAABBObjects().size()) {
		return;
	}

	curr_object = scene_objects[aabb_index * 3];
	printf("%s now selected in scene %s\n", curr_object->getName().c_str(), name.c_str());
}