/* Class representing a point light */

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

/* The maximum number of point lights allowed (must correspond with the
number in the fragment shader). */
#define MAX_POINT_LIGHTS 4

class PointLight : public Light {
public:
    /* Creates a new PointLight with the specified ambient, diffuse, and specular terms at the
    specified position with the given intensity. Reports an error if the maximum number of lights
    has been created already. */
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float light_intensity);

    /* Returns the position of this light (in world coordinates). */
    glm::vec3 getPosition();

private:
    /* Update the position uniform for this light. */
    void updatePositionUniform();

    /* Update the ambient uniform for this light */
    virtual void updateAmbientUniform();

    /* Update the diffuse uniform for this light */
    virtual void updateDiffuseUniform();

    /* Update the specular uniform for this light */
    virtual void updateSpecularUniform();

    /* Update the intensity uniform for this light. */
    virtual void updateIntensityUniform();

    /* Update uniform to indicate number of point lights active. */
    void updateNumPLightsUniform();

    /* Position of this light (in world coordinates) */
    glm::vec3 pos;

    /* Name of the position uniform for this light. */
    std::string positionUniformName;

    /* Number of point light created so far. */
    static int num_plights_created;
};

#endif