#version 330

/* The algorithm used here for generating grass is outlined at
http://http.developer.nvidia.com/GPUGems/gpugems_ch07.html */

uniform mat4 perspectiveMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

layout (triangles) in;
layout (triangle_strip, max_vertices = 15) out;

in vec4 g_world_position[];
in vec4 g_eye_position[];
in vec2 g_texcoord[];
in vec3 g_normal[];
in vec3 g_eye_normal[];

out vec4 f_world_position;
out vec4 f_eye_position;
out vec2 f_texcoord;
out vec3 f_normal;
out vec3 f_eye_normal;
out vec2 f_is_grass; //second component is ignored

void initOutVariables(int i, int is_grass) {
	f_world_position = g_world_position[i];
	f_eye_position = g_eye_position[i];
	f_texcoord = g_texcoord[i];
	f_normal = g_normal[i];
	f_eye_normal = g_eye_normal[i];
	f_is_grass = vec2(is_grass, 0);
}

void initOutVariables(int i, int is_grass, vec2 texcoord, vec3 normal) {
	f_world_position = g_world_position[i];
	f_eye_position = g_eye_position[i];
	f_texcoord = texcoord;
	f_normal = normal;
	f_eye_normal = g_eye_normal[i];
	f_is_grass = vec2(is_grass, 0);
}

void genHorizontalGrassPlane(int i, vec4 position, float width, float height, float length) {
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, 0, 0, 0));
	initOutVariables(i, 1, vec2(0, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, height, 0, 0));
	initOutVariables(i, 1, vec2(0, 1), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, 0, 0, 0));
	initOutVariables(i, 1, vec2(1, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, height, 0, 0));
	initOutVariables(i, 1, vec2(1, 1), vec3(0, 1, 0));
	EmitVertex();

	EndPrimitive();
}

void genDiagonalGrassPlaneA(int i, vec4 position, float width, float height, float length) {
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, 0, -length/2, 0));
	initOutVariables(i, 1, vec2(0, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, height, -length/2, 0));
	initOutVariables(i, 1, vec2(0, 1), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, 0, length/2, 0));
	initOutVariables(i, 1, vec2(1, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, height, length/2, 0));
	initOutVariables(i, 1, vec2(1, 1), vec3(0, 1, 0));
	EmitVertex();

	EndPrimitive();
}

void genDiagonalGrassPlaneB(int i, vec4 position, float width, float height, float length) {
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, 0, length/2, 0));
	initOutVariables(i, 1, vec2(0, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(-width/2, height, length/2, 0));
	initOutVariables(i, 1, vec2(0, 1), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, 0, -length/2, 0));
	initOutVariables(i, 1, vec2(1, 0), vec3(0, 1, 0));
	EmitVertex();

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * (position + vec4(width/2, height, -length/2, 0));
	initOutVariables(i, 1, vec2(1, 1), vec3(0, 1, 0));
	EmitVertex();

	EndPrimitive();
}

void main() {
	//generate the landscape triangle
	for (int i = 0; i < gl_in.length(); i++) {
		gl_Position = gl_in[i].gl_Position;
		initOutVariables(i, 0);
		EmitVertex();
	}
	EndPrimitive();

	//create grass blades
	for (int i = 0; i < gl_in.length(); i++) {
		//check to see if grass should be generated at this location (it should not grow on rock or dirt)
		float tex_dot_prod = dot(g_normal[i], vec3(0, 1, 0));
		if (length(g_eye_position[i]) > 50 || tex_dot_prod < 0.98) {
		    continue;
		}

		float width = 1.15f;
		float height = 0.45f;
		float length = 1.15f;
		vec4 position = g_world_position[i];

		genHorizontalGrassPlane(i, position, width, height, length);
		genDiagonalGrassPlaneA(i, position, width, height, length);
		genDiagonalGrassPlaneB(i, position, width, height, length);
	}
}