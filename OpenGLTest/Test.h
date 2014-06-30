/* Set of test functions. */

#ifndef TEST_H
#define TEST_H

#include "RenderableObject.h"
#include "OBJObject.h"
#include "HeightmapObject.h"
#include "Light.h"
#include "PointLight.h"

/* Generates a front-facing square that needs to deleted by the user. The center of the square is
at 'center_location' and the size of the square is determined by 'scaling_factor'.*/
RenderableObject* genTestSquare(glm::vec3 center_location, float scaling_factor);

/* Generates a tower loaded from an obj file that needs to be deleted by the user. */
OBJObject* genTower();

/* Generates the Blender Suzanne model from an obj dile tht needs to be deleted by the user.
Source file comes from https://github.com/OpenGLInsights/OpenGLInsightsCode/blob/master/Chapter%2026%20Indexing%20Multiple%20Vertex%20Arrays/article/suzanne.obj */
OBJObject* genSuzanne();

/* Generates a heightmap object that needs to be deleted by the user. */
HeightmapObject* genHeightmapObject();

#endif