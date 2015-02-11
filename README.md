# OpenGLTest
![](https://github.com/sksharan/OpenGLTest/blob/master/OpenGLTest/photos/opengltest.jpg)

**OpenGLTest** is a test program for that I wrote to learn more about OpenGL and graphics programming in general. The libraries used include SDL, GLEW, GLM, SOIL, and libnoise. Images of the program in action can be found at https://github.com/sksharan/OpenGLTest/tree/master/OpenGLTest/photos. 

Features
--------
- Procedurally generates a landscape using Perlin noise with textures based on the slope of the land (rock on steep land and grass on flat land). The landscape is infinite and generated in chunks, with grass blades generated on the terrain through the use of a geometry shader. A more advanced version of this terrain generation (with LOD and multithreading) can be found at https://github.com/sksharan/TerrainGenerator.
- Supports multiple methods for creating objects in the scene. A <code>RenderableObject</code> is any object that can be rendered to the screen. An <code>OBJObject</code> is a <code>RenderableObject</code> with data that comes from Wavefront OBJ files; this project implements a basic OBJ parser but there are also libraries like Assimp that can handle parsing (http://assimp.sourceforge.net/). A <code>HeightmapObject</code> is a grid-based <code>RenderableObject</code> with height values given by a greyscale "heightmap" image. A <code>PerlinHeightmapObject</code> is much like a <code>HeightmapObject</code> but with height values given by a Perlin noise equation. The infinite landscape is made up of multiple instances of <code>PerlinHeightmapObject</code>. 
- Axis-Aligned Bounding Boxes (AABBs) and Oriented Bounding Boxes (OBBs) are created for each object. AABBs and OBBs are called <code>AABBObject</code> and <code>OBBObject</code> in the code, and both are subclasses of <code>RenderableObject</code>.
- Objects can be selected by clicking on them. A ray casting technique is used with AABBs to implement this mouse picking.
- Objects can be transformed and manipulated independently of other objects (see the "Controls" section to see how objects can be manipulated).

Controls
--------
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
**L**: Toggles lighting calculations on the current object on/off. (Phong-reflection model is implemented per-fragment.)<br></br>
**T**: Toggles global wireframe rendering on/off.<br></br>
**Y**: Toggles between walk mode and fly mode.<br></br>
**Z**: Change to translate mode. Current object can then be translated using the ARROW KEYS, LSHIFT, and SPACEBAR.<br></br>
**X**: Change to scale mode. Current object can then be scaled using the LEFT/RIGHT ARROW KEYS.<br></br>
**C**: Change to rotate mode. Current object can then be rotated using the ARROW KEYS.<br></br>
**1**: Generates a checkerboard-textured square (a <code>RenderableObject</code>) at the user’s current location.<br></br>
**2**: Generates a tower object (an <code>OBJObject</code>) at the user’s current location.<br></br>
**3**: Generates a <code>HeightmapObject</code> at the user’s current location.<br></br>
**4**: Generates a <code>PerlinHeightmapObject</code> at the user’s current location.<br></br>

