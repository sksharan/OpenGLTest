#version 330

uniform mat4 perspectiveMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec2 v_texcoord;
layout(location = 2) in vec3 v_normal;

out vec4 g_world_position;
out vec4 g_eye_position;
out vec2 g_texcoord;
out vec3 g_normal;
out vec3 g_eye_normal;

void main() {
	g_world_position = modelMatrix * vec4(v_vertex, 1.0f);             //in world space
    g_eye_position = viewMatrix * g_world_position;                    //in eye space
    gl_Position = perspectiveMatrix * g_eye_position;                  //in clip space

	g_texcoord = v_texcoord;

	g_normal = v_normal;
	g_eye_normal = normalize(normalMatrix * v_normal);                 //in eye space
}