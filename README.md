
OpenGLTest is a C++ program I’ve been writing to learn more about OpenGL and graphics programming in general.

Currently, this program offers the following features:
<br>•	Implementation of the Phong reflection model using point lights
<br>•	Object creation via Wavefront OBJ files (files that encode information about 3D models)
<br>•	Terrain creation via height maps (greyscale images that encode height information)
<br>•	Generation of procedural, multi-textured landscapes using Perlin noise
<br>•	Procedurally-generated grass that renders only within a certain distance of the user and only on appropriate surfaces (e.g. grass won’t grow on a steep rocky cliff)
<br>•	Creation of Axis-Aligned Bounding Boxes (AABB) and Oriented Bounding Boxes (OBB) for all objects
<br>•	Users can generate a set of predefined objects through simple key presses
<br>•	Two movement modes: users can freely fly around the scene or simulate walking on the landscape itself
<br>•	Settings of one object (e.g. visibility, lighting, scale, position) can be modified independently of all other objects in the scene
<br>•	Objects can be selected by clicking on them with the mouse cursor (this mouse-picking is done via an algorithm that checks for ray-AABB intersections)<br/>

A more detailed description of the program (in pdf format) can be found at https://github.com/sksharan/OpenGLTest/tree/master/OpenGLTest/readme

And images from the program can be found at
https://github.com/sksharan/OpenGLTest/tree/master/OpenGLTest/photos

![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/scene.jpg)
![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/pointlight.jpg)
