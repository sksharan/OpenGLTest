#include "Ray.h"

Ray::Ray() {
    o = glm::vec3(0, 0, 0);
    d = glm::vec3(0, 0, -1);
}

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
    o = origin;
    d = direction;
}

glm::vec3 Ray::getPos(float t) {
    return o + t * d;
}