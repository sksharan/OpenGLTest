#include "MouseHandler.h"
#include "Viewer.h"
#include "Window.h"
#include "ProgramState.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include "Viewer.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <limits>
#include <iostream>

#define MOUSEHANDLER_MOVEMENT_DEBUG 0
#define MOUSEHANDLER_RAYWORLD_DEBUG 0
#define MOUSEHANDLER_VIEWERPOS_DEBUG 0
#define MOUSEHANDLER_AABB_INTERSECTION_DEBUG 0

/* These varaibles are used in handleMouseMovement() */
Uint32 old_time = 0;
Uint32 current_time = 0;
float horizontal_angle = 3.14f;
float vertical_angle = 0.0f;

//Function prototypes
void selectObjWithAABBIntersection(Scene& scene, Ray& ray);

/* Implementation adapted from
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
void handleMouseMovement(Scene& scene) {
    //if the user does not want to use the mouse to look around, skip the mouse-look calculations
    if (!programState.mouseLookModeEnabled) {
        return;
    }

    old_time = current_time;
    current_time = SDL_GetTicks();
    delta_time = float(current_time - old_time) / 1000.0f;

    // Get current mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Reset mouse position
    int half_width = mainWindow.width / 2;
    int half_height = mainWindow.height / 2;
    SDL_WarpMouseInWindow(mainWindow.window, half_width, half_height);

    // Compute new orientation
    horizontal_angle += mouse_speed * delta_time * float(mainWindow.width / 2 - x);
    vertical_angle += mouse_speed * delta_time * float(mainWindow.height / 2 - y);

    // Calculate direction
    glm::vec3 newDirection = glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
        sin(vertical_angle),
        cos(vertical_angle) * cos(horizontal_angle));

    // Calculate the right vector
    glm::vec3 newRightVector = glm::vec3(sin(horizontal_angle - 3.14f / 2.0f),
        0,
        cos(horizontal_angle - 3.14f / 2.0f));

    // Calculate the up vector
    glm::vec3 newUpVector = glm::cross(newRightVector, newDirection);

    // Update the Viewer's direction, right, and up vectors
    mainViewer.setDirection(newDirection);
    mainViewer.setRightVector(newRightVector);
    mainViewer.setUpVector(newUpVector);

    if (MOUSEHANDLER_MOVEMENT_DEBUG) {
        printf("viewer direction: %f, %f, %f\n", newDirection.x, newDirection.y, newDirection.z);
    }

    // Update the view matrix
    glm::mat4 viewMatrix = glm::lookAt(mainViewer.getPosition(), mainViewer.getPosition() + mainViewer.getDirection(),
        mainViewer.getUpVector());
    programState.viewMatrix = viewMatrix;
    for (int i = 0; i < programState.allPrograms.size(); i++) {
        updateUniformView(programState.allPrograms[i]);
    }
}


void handleMouseClick(SDL_Event event, Scene& scene) {
    //handle left click (see: http://antongerdelan.net/opengl/raycasting.html)
    if (event.button.button == SDL_BUTTON_LEFT) {

        //get the viewport coordinates
        int screen_x = event.button.x;
        int screen_y = event.button.y;

        //transform to normalized device coordinates
        float ndc_x = 2.0f * (float)screen_x / (float)mainWindow.width - 1.0f;
        float ndc_y = 1.0f - (2.0f * (float)screen_y) / (float)mainWindow.height;
        glm::vec3 ray_ndc = glm::vec3(ndc_x, ndc_y, 1.0f);

        //transform to homogeneous clip coordinates (ray has no depth so no need to reverse the perspective divide)
        glm::vec4 ray_clip = glm::vec4(ray_ndc.x, ray_ndc.y, -1.0f, 1.0f);

        //transform to eye scape
        glm::vec4 ray_eye = glm::inverse(programState.perspectiveMatrix) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

        //transform to world space
        glm::vec3 ray_world = glm::vec3(glm::inverse(programState.viewMatrix) * ray_eye);
        ray_world = glm::normalize(ray_world);

        if (MOUSEHANDLER_RAYWORLD_DEBUG) {
            printf("ray_world: %f %f %f\n", ray_world.x, ray_world.y, ray_world.z);
        }

        if (MOUSEHANDLER_VIEWERPOS_DEBUG) {
            glm::vec3 p = mainViewer.getPosition();
            printf("viewer direction: %f, %f, %f\n", p.x, p.y, p.z);
        }

        //create a ray object whose origin is at the viewer's current location.
        Ray ray(mainViewer.getPosition(), ray_world);

        selectObjWithAABBIntersection(scene, ray);
    }
}

/* Select the closest object in the 'scene' that the 'ray' intersects. Uses ray-AABB intersection. */
void selectObjWithAABBIntersection(Scene& scene, Ray& ray) {
    int index = -1;  //the index of the closest AABB that the ray intersects 
    int tmin = 100000;  //the time at which the ray intersects the closest AABB

    for (int i = 0; i < scene.getAABBObjects().size(); i++) {
        AABBObject* aabb = scene.getAABBObjects()[i];

        int t;
        if (aabb->rayIntersects(ray, t) && t < tmin) {
            tmin = t;
            index = i;

            if (MOUSEHANDLER_AABB_INTERSECTION_DEBUG) {
                std::cout << tmin << " " << aabb->getName() << std::endl;
            }
        }
    }

    if (index == -1) {
        return;  //no intersection occured, so return
    }
    else {
        scene.setCurrObjectWithAABBIndex(index);
    }
}