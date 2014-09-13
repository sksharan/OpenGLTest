#ifndef OBJECTGENERATOR_H
#define OBJECTGENERATOR_H

#include "RenderableObject.h"
#include "OBJObject.h"
#include "HeightmapObject.h"
#include "PerlinHeightmapObject.h"

/* Generates a front-facing square that needs to deleted by the user. The size of the square
is determined by 'scaling_factor'.*/
RenderableObject* genTestSquare(float scaling_factor);

/* Generates a tower loaded from an obj file that needs to be deleted by the user. */
OBJObject* genTower();

/* Generates a heightmap object that needs to be deleted by the user. */
HeightmapObject* genHeightmapObject();

/* Generates a heightmap whose height values are determined by Perlin noise equations.
'start_loc' is the point to start generating the object from and will influence the
geometry of the generated object. 'length' determines the dimensions of the heightmap. */
PerlinHeightmapObject* genPerlinHeightmapObject(glm::vec3 start_loc, int length);

#endif