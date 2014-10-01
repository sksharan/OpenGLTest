#include "ObjectDeleter.h"

void deleteObjects() {
    for (unsigned int i = 0; i < RenderableObject::getRenderableObjects().size(); i++) {
        delete RenderableObject::getRenderableObjects()[i];
    }
    for (unsigned int i = 0; i < OBJObject::getOBJObjects().size(); i++) {
        delete OBJObject::getOBJObjects()[i];
    }
    for (unsigned int i = 0; i < HeightmapObject::getHeightmapObjects().size(); i++) {
        delete HeightmapObject::getHeightmapObjects()[i];
    }
    for (unsigned int i = 0; i < AABBObject::getAABBObjects().size(); i++) {
        delete AABBObject::getAABBObjects()[i];
    }
    for (unsigned int i = 0; i < OBBObject::getOBBObjects().size(); i++) {
        delete OBBObject::getOBBObjects()[i];
    }

    // to be fixed to account for chunking algorithm
    /*for (unsigned int i = 0; i < PerlinHeightmapObject::getPerlinHeightmapObjects().size(); i++) {
        delete PerlinHeightmapObject::getPerlinHeightmapObjects()[i];
    }*/
}