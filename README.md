
OpenGLTest is a C++ program for Windows that I’ve been writing to learn more about OpenGL and graphics programming in general. The code can be built and run via the Microsoft Visual Studio Solution file included with the source code. Support for OpenGL 3.3 or higher is required to run the program.

Features
--------
<br>•	Generation of procedural, multi-textured landscapes using Perlin noise, and procedurally-generated grass
<br>• Chunking algorithm for landscapes that allows for infinite worlds
<br>•	Object creation via Wavefront OBJ files (files that encode information about 3D models)
<br>•	Terrain creation via height maps (greyscale images that encode height information)
<br>•	Users can generate a set of predefined objects through simple key presses
<br>• Users can apply affine transformations to these objects and change the way that they are rendered
<br>•	Axis-Aligned Bounding Boxes (AABB) and Oriented Bounding Boxes (OBB) for each object, allowing for mouse picking
<br>•	Multiple point lights can be placed, each implementing the Phong reflection model per-fragment
</br>

Using the Program
-------
When the program is started, the user starts in the middle of a procedurally generated landscape. The user can then move around the scene and generate a variety of objects, each of which can be manipulated in various ways. The landscape is generated in chunks, and as the user moves around, new chunks are created around the user, making the world infinitely large. The controls are:

<br>• <b>Moving the mouse</b>: Look around the screen. To regain control of the mouse cursor, press the M key. To go back to looking around in the scene, press the M key again.
<br>• <b>Left-click</b>: Select an object on the screen. The landscape itself cannot be selected.
<br>• <b>ESC</b>: Closes the window and terminates the program.
<br>• <b>W, A, S, D</b>: Move around the scene.
<br>• <b>M</b>: Toggles mouselook mode on/off.
<br>• <b>Q, E</b>: Select the previous/next object on the list. The name of the newly selected item is visible through the console window.
<br>• <b>R</b>: Change the rendering mode of the currently selected item. “Textured” mode shows the object when it is textured. “Normal” mode displays the normals of the object, where all normals are in eye space.
<br>• <b>H</b>: Toggles the visibility of the currently selected object. The object can still be selected even when it is hidden.
<br>• <b>J, K</b>: Toggles the visibility of the currently selected object’s AABB (red box) and OBB (blue box), respectively.
<br>• <b>L</b>: Toggles whether or not the currently selected object is influenced by lighting calculations. If it is not, then the object is rendered as if there are no lights in the scene.
<br>• <b>T</b>: Toggles wireframe rendering on/off. This affects all objects in the scene.
<br>• <b>Y</b>: Toggle movement modes. The user can freely fly about the scene or walk on the landscape.
<br>• <b>Z</b>: Change to translate mode. The current object can then be translated using the ARROW KEYS, LSHIFT,
and SPACEBAR. Translation occurs in terms of world space.
<br>• <b>X</b>: Change to scale mode. The current object can then be scaled using the LEFT/RIGHT ARROW KEYS.
<br>• <b>C</b>: Change to rotate mode. The current object can then be rotated using the ARROW KEYS. Rotation 
occurs in terms of world space.
<br>• <b>1</b>: Generates a checkerboard-textured square (a RenderableObject) at the user’s current location.
<br>• <b>2</b>: Generates a tower object (an OBJObject) at the user’s current location.
<br>• <b>3</b>: Generates a HeightmapObject at the user’s current location. A HeightmapObject is a grid-based object
whose height values at each vertex are determined by a grayscale “height map” image.
<br>• <b>4</b>: Generates a PerlinHeightmapObject at the user’s current location. They are just like HeightmapObjects except that 
the height values are determined by a Perlin noise equation.

Images
------
Images showing the program in action can be found at:
https://github.com/sksharan/OpenGLTest/tree/master/OpenGLTest/photos

![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/pointlight.jpg)

