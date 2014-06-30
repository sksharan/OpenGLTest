#ifndef ENUMRENDERMODE_H
#define ENUMRENDERMODE_H

enum RenderMode {
	RENDERMODE_TEXTURED,   // object.renderMode = 0 in fragment shader
	RENDERMODE_NORMALS     // object.renderMode = 1 in fragment shader
};

#endif