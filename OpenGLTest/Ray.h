#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

/* Class representing a ray (R) with an origin (O) and direction (D). Any point on this ray at time t is given
by the equation R(t) = O + Dt. Fields of this ray are directly accessible.  */
class Ray {
public:
    /* Makes a Ray at (0, 0, 0) facing in the -z direction. */
    Ray();

    /* Creates a new ray with origin at 'origin' and facing towards 'direction.' */
    Ray(glm::vec3 origin, glm::vec3 direction);

    /* Get a position along this ray at time t. */
    glm::vec3 getPos(float t);

    /* Ray origin.*/
    glm::vec3 o;

    /* Ray direction. */
    glm::vec3 d;
};

#endif