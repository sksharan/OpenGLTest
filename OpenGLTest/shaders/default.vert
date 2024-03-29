#version 330

/* Transformation matrices. */
uniform mat4 perspectiveMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

layout(location = 0) in vec3 v_vertex;
layout(location = 1) in vec2 v_texcoord;
layout(location = 2) in vec3 v_normal;

out vec4 f_world_position;
out vec4 f_eye_position;
out vec2 f_texcoord;
out vec3 f_normal;
out vec3 f_eye_normal;

void main() {
    f_world_position = modelMatrix * vec4(v_vertex, 1.0f);             //in world space
    f_eye_position = viewMatrix * f_world_position;                    //in eye space
    gl_Position = perspectiveMatrix * f_eye_position;                  //in clip space

    f_texcoord = v_texcoord;

    f_normal = v_normal;
    f_eye_normal = normalize(normalMatrix * v_normal);                 //in eye space
}