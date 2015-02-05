# OpenGLTest
![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/opengltest.jpg)

**OpenGLTest** is a program for that I’ve been writing to learn more about OpenGL and graphics programming in general. The libraries used include SDL, GLEW, GLM, SOIL, and libnoise.

The program creates an infinite procedural, multi-textured landscape using Perlin noise. The landscape is generated in chunks, and grass blades are generated on the terrain through the use of a geometry shader.

The program supports multiple methods for creating objects in the scene. A <code>RenderableObject</code> is any object that can be rendered to the screen, and all of the following object types are subclasses of <code>RenderableObject</code>. An <code>OBJObject</code> is an object with the data that comes from Wavefront OBJ files; this project implements a basic OBJ parser but there are also libraries like Assimp that can handle parsing (http://assimp.sourceforge.net/). A <code>HeightmapObject</code> is a grid-based object with height values given by a greyscale 'heightmap' image. A <code>PerlinHeightmapObject</code> is much like a <code>HeightmapObject</code> but with height values given by a Perlin noise equation, and the infinite landscape is made up of multiple instances of <code>PerlinHeightmapObject</code>. 

The controls are:
**Moving the mouse**: Look around the scene.<br></br>
**Left-click**: Select an object on the screen. (The infinite landscape cannot be selected.)<br></br>
**ESC**: Ends the program.<br></br>
**W, A, S, D**: Move around the scene.<br></br>
**M**: Toggles mouselook mode on/off.<br></br>
**Q, E**: Select the previous/next object on the list. (Current object is shown on the console).<br></br>
**R**: Change the rendering mode of the currently selected item.<br></br>
**H**: Toggles the visibility of the currently selected object..<br></br>
**J**: Toggles the visibility of the currently selected object’s AABB (red box).<br></br>
**K**: Toggles the visibility of the currently selected object’s OBB (blue box).<br></br>
**L**: Toggles lighting calculations on the current object on/off.<br></br>
**T**: Toggles global wireframe rendering on/off.<br></br>
**Y**: Toggles between walk mode and fly mode.<br></br>
**Z**: Change to translate mode. The current object can then be translated using the ARROW KEYS, LSHIFT,
and SPACEBAR. Translation occurs in terms of world space.<br></br>
**X**: Change to scale mode. The current object can then be scaled using the LEFT/RIGHT ARROW KEYS.<br></br>
**C**: Change to rotate mode. The current object can then be rotated using the ARROW KEYS. Rotation 
occurs in terms of world space.<br></br>
**1**: Generates a checkerboard-textured square (a <code>RenderableObject</code>) at the user’s current location.<br></br>
**2**: Generates a tower object (an <code>OBJObject</code>) at the user’s current location.<br></br>
**3**: Generates a <code>HeightmapObject</code> at the user’s current location.<br></br>
**4**: Generates a <code>PerlinHeightmapObject</code> at the user’s current location.<br></br>

