Updates:

6/3/14 (first commit):
- Created an OpenGL program that renders textured objects to the screen. The vertices, texture coordinates, and normals for these objects can be specified manually or from Wavefront OBJ files (a common format used by 3D modelling programs like Blender). The window is created using SDL 2.0, and GLEW is used to access additional OpenGL functions. GLM is used for simpler matrix calculations.
- Implemented basic keyboard support (W, A, S, D to move and T to toggle between filled and wireframe mode)
- Implemented mouse support (move mouse to look around)
- The RenderableObject class is the base class for all objects that can be rendered to the screen. Every RenderableObject has a render() method that is called when that object is to be rendered. This class also keeps track of all RenderableObjects made in the program's lifetime (including children of RenderableObject).
- OBJObject is a child class of Renderable object. It is used for classes whose data comes from Wavefront OBJ files.
- The Viewer class is used to represent any entity that looks into the world. It is used here to represent the user's view into the rendered world.
- Main.cpp contains the entry point of the program and is also home to the main loop.
- Added the isosphere obj to the obj folder and added its corresponding texture to the textures folder. Added example photos of the program in action to the photos folder.

6/15/14:
- Modified OBJObject so the rendering is done without the use of element arrays (meaning it doesn't do indexed drawing). To facilitate this, many methods and fields were removed. The parseOBJ() method was modified accordingly. Doing the rendering in this way means that OBJ files exported from 3D programs can be used without any modification.
- Added tower.obj to the obj folder and added tower.jpg to the textures folder. This tower and its associated texture were made in Blender. Removed the old isosphere files and added new example photos to the photos folder.
- Other minor changes like adding comments

6/16/14:
- Added a new HeightmapObject class that inherits from RenderableObject. A HeightmapObject is an n-by-n grid that extends in the positive x and negative z axes. The y-coordinate of each point on the grid is determined by a grayscale image called a heightmap. The user can specify the number of vertices that make up one side of the HeightmapObject, which position to start making the heightmap from, the amplitude of the height values, and how far vertices are from each other. If a HeightmapObject is n-by-n vertices, then it is required that the corresponding heightmap image is n-by-n pixels in size.
- Started working on adding lighting
