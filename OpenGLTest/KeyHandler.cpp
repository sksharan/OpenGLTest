#include "KeyHandler.h"
#include "ProgramState.h"
#include "Window.h"
#include "MatrixTransform.h"
#include "Constants.h"
#include "MatrixTransform.h"
#include "Viewer.h"
#include "RenderableObject.h"
#include "AABBObject.h"
#include "OBBObject.h"
#include "EnumRenderMode.h"
#include "EnumTransformation.h"
#include "LandscapeManager.h"
#include "ObjectGenerator.h"
#include <SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/* Keyboard-related controls:
    ESC : end program
    M : toggle mouse-look mode on/off
    W, A, S, D : move the viewer
    Q : select previous object
    E : select next object
    R : switching rendering mode of the currently selected object
    H : toggle visibility of the currently selected object
    J : hide AABB of the currently selected object
    K : hide OBB of the currently selected object
    L : toggle whether or not the currently selected object is affected by lighting calculations
    T : toggle wireframe mode on/off
    Y : toggle free-flying camera mode on/off
    Z : change to translate mode (then manipulate object with ALL ARROW KEYS, LSHIFT, SPACEBAR)
    X : change to scale mode (then manipulate object with LEFT AND RIGHT ARROW KEYS)
    C : change to rotate mode (then manipulate object with ALL ARROW KEYS)
    1 : generate a test square (RenderableObject) at the viewer's location
    2 : generate a tower (OBJObject) at the viewer's location
    3 : generate a HeightmapObject at the viewer's location
    4 : generate a PerlinHeightmapObject at the viewer's location
    */

#define KEYHANDLER_DEBUG 0

const Uint8* keystate = SDL_GetKeyboardState(NULL);

Transformation transformationMode = TRANSLATE;

/* Function protoypes. */
void handleObjects(SDL_Event event, Scene& scene);
void setAABB(std::string currObjName);
void setOBB(std::string currObjName);

/* Adapted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/ */
void handleKeyInput(Scene& scene) {
    /* W : move forward */
    if (keystate[SDL_SCANCODE_W]) {
        glm::vec3 position = mainViewer.getPosition();
        position += mainViewer.getDirection() * delta_time * movement_speed;
        if (!programState.noClipEnabled) {
            if (landscapeManager.getRegisteredLandscape(mainViewer) == NULL) {
                std::cout << "no landscape to walk on!" << std::endl;
            }
            else {
                position.y = landscapeManager.getRegisteredLandscape(mainViewer)->getY(position.x, position.z) + programState.userHeight;
            }
        }
        mainViewer.setPosition(position);

        if (KEYHANDLER_DEBUG) {
            printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
        }
    }

    /* A : move left */
    if (keystate[SDL_SCANCODE_A]) {
        glm::vec3 position = mainViewer.getPosition();
        position -= mainViewer.getRightVector() * delta_time * movement_speed;
        if (!programState.noClipEnabled) {
            if (landscapeManager.getRegisteredLandscape(mainViewer) == NULL) {
                std::cout << "no landscape to walk on!" << std::endl;
            }
            else {
                position.y = landscapeManager.getRegisteredLandscape(mainViewer)->getY(position.x, position.z) + programState.userHeight;
            }
        }
        mainViewer.setPosition(position);

        if (KEYHANDLER_DEBUG) {
            printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
        }
    }

    /* S : move backward */
    if (keystate[SDL_SCANCODE_S]) {
        glm::vec3 position = mainViewer.getPosition();
        position -= mainViewer.getDirection() * delta_time * movement_speed;
        if (!programState.noClipEnabled) {
            if (landscapeManager.getRegisteredLandscape(mainViewer) == NULL) {
                std::cout << "no landscape to walk on!" << std::endl;
            }
            else {
                position.y = landscapeManager.getRegisteredLandscape(mainViewer)->getY(position.x, position.z) + programState.userHeight;
            }
        }
        mainViewer.setPosition(position);

        if (KEYHANDLER_DEBUG) {
            printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
        }
    }

    /* D : move right */
    if (keystate[SDL_SCANCODE_D]) {
        glm::vec3 position = mainViewer.getPosition();
        position += mainViewer.getRightVector() * delta_time * movement_speed;
        if (!programState.noClipEnabled) {
            if (landscapeManager.getRegisteredLandscape(mainViewer) == NULL) {
                std::cout << "no landscape to walk on!" << std::endl;
            }
            else {
                position.y = landscapeManager.getRegisteredLandscape(mainViewer)->getY(position.x, position.z) + programState.userHeight;
            }
        }
        mainViewer.setPosition(position);

        if (KEYHANDLER_DEBUG) {
            printf("viewer position: %f, %f, %f\n", position.x, position.y, position.z);
        }
    }
}

void handleKeyInputNC(SDL_Event event, Scene& scene) {
    switch (event.key.keysym.sym) {

        /* ESC: exit program */
    case SDLK_ESCAPE:
        programState.done = true;
        break;

        /* T : toggle wirframe mode on/off */
    case SDLK_t:
        if (programState.wireframeEnabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        programState.wireframeEnabled = !programState.wireframeEnabled;
        break;

        /* Y : toggle free-flying camera mode on/off */
    case SDLK_y:
        programState.noClipEnabled = !programState.noClipEnabled;
        break;

        /* M: toggle mouse-look mode on/off */
    case SDLK_m:
        SDL_WarpMouseInWindow(mainWindow.window, mainWindow.width / 2, mainWindow.height / 2); //force mouse to center of screen
        programState.mouseLookModeEnabled = !programState.mouseLookModeEnabled;
        if (programState.mouseLookModeEnabled) {
            SDL_ShowCursor(0);
        }
        else {
            SDL_ShowCursor(1);
        }
        break;

    default:
        break;
    }

    handleObjects(event, scene);
}

/* Function that specifically handles selection and manipulation of objects, given
an SDL_Event. */
void handleObjects(SDL_Event event, Scene& scene) {
    RenderableObject* object;
    switch (event.key.keysym.sym) {
        /* 1 : generate a test square (RenderableObject) at the viewer's location */
    case SDLK_1:
        object = genTestSquare(3.0f);
        object->setModelMatrix(glm::translate(object->getModelMatrix(), glm::vec3(mainViewer.getPosition().x, mainViewer.getPosition().y, mainViewer.getPosition().z)));
        scene.addObject(object);
        break;

        /* 2 : generate a tower (OBJObject) at the viewer's location */
    case SDLK_2:
        object = genTower();
        object->setModelMatrix(glm::translate(object->getModelMatrix(), glm::vec3(mainViewer.getPosition().x, mainViewer.getPosition().y, mainViewer.getPosition().z)));
        scene.addObject(object);
        break;

        /* 3 : generate a HeightmapObject at the viewer's location */
    case SDLK_3:
        object = genHeightmapObject();
        object->setModelMatrix(glm::translate(object->getModelMatrix(), glm::vec3(mainViewer.getPosition().x, mainViewer.getPosition().y, mainViewer.getPosition().z)));
        scene.addObject(object);
        break;

        /* 4 : generate a PerlinHeightmapObject at the viewer's location */
    case SDLK_4:
        object = genPerlinHeightmapObject(mainViewer.getPosition(), 64);
        //object->setModelMatrix(glm::translate(object->getModelMatrix(), glm::vec3(mainViewer.getPosition().x, mainViewer.getPosition().y, mainViewer.getPosition().z)));
        scene.addObject(object);
        break;

    default:
        break;
    }


    RenderableObject* currObject = scene.getCurrObject();
    if (currObject == NULL) {
        return;  //return if there are no objects to manipulate
    }
    switch (event.key.keysym.sym) {

        /* E: go to next object. */
    case SDLK_e:
        scene.changeToNextObject();
        break;

        /* Q: go to previous object. */
    case SDLK_q:
        scene.changeToPrevObject();
        break;

        /* R: change the rendering mode of the currently selected object. */
    case SDLK_r:
        if (currObject->getRenderMode() == RENDERMODE_NORMALS) {
            currObject->setRenderMode(RENDERMODE_TEXTURED);
            printf("changing render mode of %s to RENDERMODE_TEXTURED\n", scene.getCurrObject()->getName().c_str());
        }
        else {
            currObject->setRenderMode(RENDERMODE_NORMALS);
            printf("changing render mode of %s to RENDERMODE_NORMALS\n", scene.getCurrObject()->getName().c_str());
        }
        break;

        /* H: toggle visibility of the currently selected object. */
    case SDLK_h:
        currObject->toggleVisibilty();
        scene.getCurrOBB()->calculateOBB();
        break;

        /* J : hide AABB of the currently selected object */
    case SDLK_j:
        scene.getCurrAABB()->toggleVisibilty();
        if (scene.getCurrAABB()->isVisible()) {
            scene.getCurrAABB()->calculateAABB();
        }
        break;

        /* K: hide OBB of the currently selected object */
    case SDLK_k:
        scene.getCurrOBB()->toggleVisibilty();
        if (scene.getCurrOBB()->isVisible()) {
            scene.getCurrOBB()->calculateOBB();
        }
        break;

        /* L : toggle whether or not the currently selected object is affected by lighting calculations. */
    case SDLK_l:
        currObject->toggleLightEnabledStatus();
        break;

        /* Z: switch to translate mode .*/
    case SDLK_z:
        transformationMode = TRANSLATE;
        std::cout << "switching to translation mode" << std::endl;
        break;

        /* X: switch to scale mode .*/
    case SDLK_x:
        transformationMode = SCALE;
        std::cout << "switching to scaling mode" << std::endl;
        break;

        /* C: switch to rotate mode .*/
    case SDLK_c:
        transformationMode = ROTATE;
        std::cout << "switching to rotation mode" << std::endl;
        break;

        /* UP ARROW: depends on currently selected object (see Controls comment at top of file) */
    case SDLK_UP:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, 0.0f, -translation_factor)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            //does nothing
        }
        else if (transformationMode == ROTATE) {
            currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), rotation_factor, glm::vec3(1.0f, 0.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        break;

        /* DOWN ARROW: depends on currently selected object (see Controls comment at top of file) */
    case SDLK_DOWN:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, 0.0f, translation_factor)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            //does nothing
        }
        else if (transformationMode == ROTATE) {
            currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), -rotation_factor, glm::vec3(1.0f, 0.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        break;

        /* LEFT ARROW: depends on currently selected object (see Controls comment at top of file) */
    case SDLK_LEFT:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(-translation_factor, 0.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            currObject->setModelMatrix(glm::scale(currObject->getModelMatrix(), glm::vec3(1.0 / scaling_factor, 1.0 / scaling_factor, 1.0 / scaling_factor)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == ROTATE) {
            currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), -rotation_factor, glm::vec3(0.0f, 1.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        break;

        /* RIGHT ARROW: depends on currently selected object (see Controls comment at top of file) */
    case SDLK_RIGHT:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(translation_factor, 0.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            currObject->setModelMatrix(glm::scale(currObject->getModelMatrix(), glm::vec3(scaling_factor, scaling_factor, scaling_factor)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == ROTATE) {
            currObject->setModelMatrix(glm::rotate(currObject->getModelMatrix(), rotation_factor, glm::vec3(0.0f, 1.0f, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        break;

        /* LSHIFT : depends on currently selected object (see Controls comment at top of file) */
    case SDLK_LSHIFT:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, -translation_factor, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            //does nothing
        }
        else if (transformationMode == ROTATE) {
            //does nothing
        }
        break;

        /* SPACEBAR : depends on currently selected object (see Controls comment at top of file) */
    case SDLK_SPACE:
        if (transformationMode == TRANSLATE) {
            currObject->setModelMatrix(glm::translate(currObject->getModelMatrix(), glm::vec3(0.0f, translation_factor, 0.0f)));
            if (scene.getCurrAABB()->isVisible()) scene.getCurrAABB()->calculateAABB();
            if (scene.getCurrOBB()->isVisible()) scene.getCurrOBB()->calculateOBB();
        }
        else if (transformationMode == SCALE) {
            //does nothing
        }
        else if (transformationMode == ROTATE) {
            //does nothing
        }
        break;

    default:
        break;
    }
}