/* Set of test functions. */

#ifndef TEST_H
#define TEST_H

#include "RenderableObject.h"
#include "OBJObject.h"
#include "HeightmapObject.h"
#include "Light.h"
#include "PointLight.h"

/* Generates a front-facing square that needs to deleted by the user. */
RenderableObject* genTestSquare();

/* Generates a tower loaded from an obj file that needs to be deleted by the user. */
OBJObject* genTower();

/* Generates a heightmap object that needs to be deleted by the user. */
HeightmapObject* genHeightmapObject();

/* Generates a PointLight object that needs to be deleted by the user. */
PointLight* genPointLight();

#endif