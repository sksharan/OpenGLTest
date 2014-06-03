OpenGLTest
==========
This project currently uses OpenGL 3.3 to render textured objects to the screen.
The data for these objects can be specified manually or come from Wavefront OBJ files.
SDL 2.0 is used to create the OpenGL context, and GLEW is used to access additional OpenGL
functions. SOIL is used to load texture images.

Controls:
---------
W:   move forward

A:   move left

S:   move backward

D:   move right

T:   toggle wireframe mode on/off

ESC: close program

The mouse can be used to look around in all directions from the current position.


Some important files:
---------------------

Main.cpp : program entry point and home of the main loop

Constants.h : defines constants used across the program

ProgramState.h : defines a struct representing the state of the program (e.g. keeps track
                 of whether or not the program should continue running)

Window.h : defines the properties of the window used in the program

KeyHandler.h : handles key presses by the user

MouseHandler.h : handles mouse movements by the user

RenderableObject.h : class representing any object that can be drawn to the screen

OBJObject.h : a type of RenderableObject whose data comes from Wavefront OBJ files

Render.h : contains the function that renders objects to the screen. Calls the render()
           method of every RenderableObject created by the user
           
Test.h : makes a test RenderableObject

MatrixTransform.h : updates uniforms for the modelview and perspective matrices

Util.h : utility functions including one that reads files and returns their contents

Viewer.h : class representing an entity that looks into the world


Some important folders: 
-----------------------

photos: contains photos showing what the program does at runtime

textures: contains texture images (rock.jpg is from CGTextures.com)

shaders: contains files for the OpenGL shaders


TODO list:
-----------
- add a Heightmap class, a type of RenderableObject that pertains to geometry generated
  from greyscale heightmap images

- implement lighting
