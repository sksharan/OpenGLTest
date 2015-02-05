# OpenGLTest
![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/opengltest.jpg)

**OpenGLTest** is a program for that I’ve been writing to learn more about OpenGL and graphics programming in general. The libraries used include SDL, GLEW, GLM, SOIL, and libnoise.

The program creates an infinite procedural, multi-textured landscape using Perlin noise. The landscape is generated in chunks, and grass blades are generated on the terrain through the use of a geometry shader.

The program supports multiple methods for creating objects in the scene. A <code>RenderableObject</code> is any object that can be rendered to the screen, and all of the following object types are subclasses of <code>RenderableObject</code>. An <code>OBJObject</code> is an object with the data that comes from Wavefront OBJ files; this project implements a basic OBJ parser but there are also libraries like Assimp that can handle parsing (http://assimp.sourceforge.net/). A <code>HeightmapObject</code> is a grid-based object with height values given by a greyscale 'heightmap' image. A <code>PerlinHeightmapObject</code> is much like a <code>HeightmapObject</code> but with height values given by a Perlin noise equation, and the infinite landscape is made up of multiple instances of <code>PerlinHeightmapObject</code>. 

<br>• <b>Moving the mouse</b>: Look around the screen. To regain control of the mouse cursor, press the M key. To go back to looking around in the scene, press the M key again.</br>
<br>• <b>Left-click</b>: Select an object on the screen. The landscape itself cannot be selected.</br>
<br>• <b>ESC</b>: Closes the window and terminates the program.</br>
<br>• <b>W, A, S, D</b>: Move around the scene.</br>
<br>• <b>M</b>: Toggles mouselook mode on/off.</br>
<br>• <b>Q, E</b>: Select the previous/next object on the list. The name of the newly selected item is visible through the console window.</br>
<br>• <b>R</b>: Change the rendering mode of the currently selected item. “Textured” mode shows the object when it is textured. “Normal” mode displays the normals of the object, where all normals are in eye space.</br>
<br>• <b>H</b>: Toggles the visibility of the currently selected object. The object can still be selected even when it is hidden.</br>
<br>• <b>J, K</b>: Toggles the visibility of the currently selected object’s AABB (red box) and OBB (blue box), respectively.</br>
<br>• <b>L</b>: Toggles whether or not the currently selected object is influenced by lighting calculations. If it is not, then the object is rendered as if there are no lights in the scene.</br>
<br>• <b>T</b>: Toggles wireframe rendering on/off. This affects all objects in the scene.</br>
<br>• <b>Y</b>: Toggle movement modes. The user can freely fly about the scene or walk on the landscape.</br>
<br>• <b>Z</b>: Change to translate mode. The current object can then be translated using the ARROW KEYS, LSHIFT,
and SPACEBAR. Translation occurs in terms of world space.</br>
<br>• <b>X</b>: Change to scale mode. The current object can then be scaled using the LEFT/RIGHT ARROW KEYS.</br>
<br>• <b>C</b>: Change to rotate mode. The current object can then be rotated using the ARROW KEYS. Rotation 
occurs in terms of world space.</br>
<br>• <b>1</b>: Generates a checkerboard-textured square (a RenderableObject) at the user’s current location.</br>
<br>• <b>2</b>: Generates a tower object (an OBJObject) at the user’s current location.</br>
<br>• <b>3</b>: Generates a HeightmapObject at the user’s current location. A HeightmapObject is a grid-based object
whose height values at each vertex are determined by a grayscale “height map” image.</br>
<br>• <b>4</b>: Generates a PerlinHeightmapObject at the user’s current location. They are just like HeightmapObjects except that the height values are determined by a Perlin noise equation.</br>

