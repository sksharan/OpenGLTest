#include "Viewer.h"

/* Definition of 'mainViewer' from Viewer.h */
Viewer mainViewer;

Viewer::Viewer() {
    position = glm::vec3(0, 0, 0);
    direction = glm::vec3(0, 0, -1);
    right = glm::vec3(1, 0, 0);
    up = glm::vec3(0, 1, 0);
}

Viewer::~Viewer() {

}

glm::vec3 Viewer::getPosition() {
    return position;
}

glm::vec3 Viewer::getDirection() {
    return direction;
}

glm::vec3 Viewer::getRightVector() {
    return right;
}

glm::vec3 Viewer::getUpVector() {
    return up;
}

void Viewer::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void Viewer::setDirection(glm::vec3 newDirection) {
    direction = glm::normalize(newDirection);
}

void Viewer::setRightVector(glm::vec3 newRightVector) {
    right = glm::normalize(newRightVector);
}

void Viewer::setUpVector(glm::vec3 newUpVector) {
    up = glm::normalize(newUpVector);
}