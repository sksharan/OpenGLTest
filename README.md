OpenGLTest
==========

OpenGLTest is a C++ program I’ve been writing to learn more about OpenGL and graphics programming in general.

Currently, this program offers the following features:
•	Implementation of the Phong reflection model using point lights
•	Object creation via Wavefront OBJ files (files that encode information about 3D models)
•	Terrain creation via height maps (greyscale images that encode height information)
•	Generation of procedural, multi-textured landscapes using Perlin noise
•	Procedurally-generated grass that renders only within a certain distance of the user and only on appropriate surfaces (e.g. grass won’t grow on a steep rocky cliff)
•	Creation of Axis-Aligned Bounding Boxes (AABB) and Oriented Bounding Boxes (OBB) for all objects
•	Users can generate a set of predefined objects through simple key presses
•	Two movement modes: users can freely fly around the scene or simulate walking on the landscape itself
•	Settings of one object (e.g. visibility, lighting, scale, position) can be modified independently of all other objects in the scene
•	Objects can be selected by clicking on them with the mouse cursor (this mouse-picking is done via an algorithm that checks for ray-AABB intersections)

A more detailed description of the program (in pdf format) can be found at https://github.com/sksharan/OpenGLTest/tree/master/OpenGLTest/readme
