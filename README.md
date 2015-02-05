# OpenGLTest
![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/opengltest.jpg)

**OpenGLTest** is a program for that I’ve been writing to learn more about OpenGL and graphics programming in general. The libraries used include SDL, GLEW, GLM, SOIL, and libnoise.

The program creates an infinite procedural, multi-textured landscape using Perlin noise. The landscape is generated in chunks, and grass blades are generated on the terrain through the use of a geometry shader.

The program supports multiple methods for creating objects in the scene. A <code>RenderableObject</code> is any object that can be rendered to the screen, and all of the following object types are subclasses of <code>RenderableObject</code>. An <code>OBJObject</code> is an object with the data that comes from Wavefront OBJ files; this project implements a basic OBJ parser but there are also libraries like Assimp that can handle parsing (http://assimp.sourceforge.net/). A <code>HeightmapObject</code> is a grid-based object with height values given by a greyscale 'heightmap' image. A <code>PerlinHeightmapObject</code> is much like a <code>HeightmapObject</code> but with height values given by a Perlin noise equation, and the infinite landscape is made up of multiple instances of <code>PerlinHeightmapObject</code>. 

**Moving the mouse**: Look around the screen. To regain control of the mouse cursor, press the M key. To go back to looking around in the scene, press the M key again.
**Left-click**: Select an object on the screen. The landscape itself cannot be selected.
**ESC**: Closes the window and terminates the program.
**W, A, S, D**: Move around the scene.
**M**: Toggles mouselook mode on/off.
**Q, E**: Select the previous/next object on the list. The name of the newly selected item is visible through the console window.
**R**: Change the rendering mode of the currently selected item. “Textured” mode shows the object when it is textured. “Normal” mode displays the normals of the object, where all normals are in eye space.
**H**: Toggles the visibility of the currently selected object. The object can still be selected even when it is hidden.
**J, K**: Toggles the visibility of the currently selected object’s AABB (red box) and OBB (blue box), respectively.
**L**: Toggles whether or not the currently selected object is influenced by lighting calculations. If it is not, then the object is rendered as if there are no lights in the scene.
**T**: Toggles wireframe rendering on/off. This affects all objects in the scene.
**Y**: Toggle movement modes. The user can freely fly about the scene or walk on the landscape.
**Z**: Change to translate mode. The current object can then be translated using the ARROW KEYS, LSHIFT,
and SPACEBAR. Translation occurs in terms of world space.
**X**: Change to scale mode. The current object can then be scaled using the LEFT/RIGHT ARROW KEYS.
**C**: Change to rotate mode. The current object can then be rotated using the ARROW KEYS. Rotation 
occurs in terms of world space.
**1**: Generates a checkerboard-textured square (a RenderableObject) at the user’s current location.
**2**: Generates a tower object (an OBJObject) at the user’s current location.
**3**: Generates a HeightmapObject at the user’s current location. A HeightmapObject is a grid-based object
whose height values at each vertex are determined by a grayscale “height map” image.
**4**: Generates a PerlinHeightmapObject at the user’s current location. They are just like HeightmapObjects except that the height values are determined by a Perlin noise equation.

