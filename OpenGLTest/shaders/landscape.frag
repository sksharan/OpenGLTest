#version 330

/* Represents a point light. */
struct PointLight {
	/* Position of this light (in world coordinates). */
    vec3 position;
	/* Ambient component */
	vec3 La;
	/* Diffuse component */
	vec3 Ld;
	/* Specular component */
	vec3 Ls;
	/* Light intensity */
	float intensity;
};

/* Represents an object in the scene. */
struct Object {
    /* Ambient component */
	vec3 Ka;
	/* Diffuse component */
	vec3 Kd;
	/* Specular component */
	vec3 Ks;
	/* Shininess factor */
	float shininess;
	/* Equal to 1 iff this object is affected by lighting calculations. */
	int light_enabled;
	/* The type of rendering to perform (see EnumRenderMode.h). */
    int renderMode;
};

/* The current object. */
uniform Object object;

/* Arrays of lights. */
uniform PointLight pLights[4];         //corresponds to MAX_POINT_LIGHTS in Constants.h

/* Number of lights currently in use. */
uniform int numPLights;               //should not exceed length of pLights

/* Samplers for the object's base textures. */
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

/* Transformation matrices. */
uniform mat4 perspectiveMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

/* Input values. */
in vec4 f_world_position;
in vec4 f_eye_position;
in vec2 f_texcoord;
in vec3 f_normal;
in vec3 f_eye_normal;
in vec2 f_is_grass; //first component (=1) only if this frag comes from grass in the geometry shader

/* Output values. */
out vec4 frag_color;

/* Test the value of the normals. Right-facing parts are red, upward-facing
parts are green, and forward-facing parts are blue. Any negative values are
clamped to 0. See http://antongerdelan.net/opengl/debugshaders.html for more details. */
vec4 testNormals() {
    return vec4(f_normal, 1.0); 
}

/* Uses the Phong lighting equation to calculate the color of this fragment as if
pLights[id] is the only light in the scene. Uses texture 'tex' */
vec3 phongForPointLight(int id, vec4 tex) {
    vec4 light_pos_eye = viewMatrix * vec4(pLights[id].position, 1.0);  //move light position into eye space

	//ambient term
	vec3 Ia = pLights[id].La * object.Ka;

	//diffuse term
	vec3 direction_to_light_eye = normalize( vec3(light_pos_eye - f_eye_position) );
	vec3 Id = pLights[id].Ld * object.Kd * max( dot(direction_to_light_eye, f_eye_normal), 0.0 );
	float texture_weight = 0.9;
	Id = mix(Id, vec3(tex), texture_weight);  //texture contributes to diffuse component

	//specular term
	vec3 reflection_eye = reflect(-direction_to_light_eye, f_eye_normal);
	vec3 direction_to_viewer_eye = normalize( -vec3(f_eye_position) );  //can do this since we're working in eye space
	float specular_dot_prod = max( dot(reflection_eye, direction_to_viewer_eye), 0.0 );
	vec3 Is = vec3(0, 0, 0);
	if (specular_dot_prod > 0.0) {
	    Is = pLights[id].Ls * object.Ks * pow(specular_dot_prod, object.shininess);
	}

	return pLights[id].intensity * (Ia + Id + Is);
}

void main() {
	/* Represents the texture used for this fragment. */
	vec4 frag_texture = vec4(0.5, 0.5, 0.5, 1);

	/* Use the dot product between the fragment normal and the up vector to calculate which texture to use. */
	float tex_dot_prod = dot(f_normal, vec3(0, 1, 0));
	if (tex_dot_prod > 1) tex_dot_prod = 0;
	vec4 grass_texture_1 = texture(texture0, f_texcoord);
	vec4 grass_texture_2 = texture(texture1, f_texcoord);
	vec4 rock_texture = texture(texture2, f_texcoord);
	vec4 dirt_texture = texture(texture3, f_texcoord);
	vec4 plant_alpha_texture = texture(texture4, f_texcoord);

	if (tex_dot_prod < 0.85) {
		frag_texture = rock_texture;
	} else if (tex_dot_prod < 0.875) {
		frag_texture = dirt_texture;
	} else if (tex_dot_prod < 0.95) {
		frag_texture = grass_texture_1;
	} else if (tex_dot_prod < 0.98) {
		frag_texture = grass_texture_2;
	} else {
		frag_texture = dirt_texture;
	}
	
	if (f_is_grass.x > 0.99) {
		frag_texture = plant_alpha_texture;
	}

	if (frag_texture.a < 0.8) {
		discard;
	}

	/* Textured rendering: if lighting is enabled, include the lighting calculations, otherwise
	 * only use the texture. */
    if (object.renderMode == 0) {

		if (object.light_enabled == 1) {
			vec3 rgb_color = vec3(0, 0, 0);
			for (int id = 0; id < numPLights; id++) {
				rgb_color += phongForPointLight(id, frag_texture);
			}
			frag_color = vec4(rgb_color, frag_texture.a);
	    } else {
			frag_color = frag_texture;
		}
	}

	/* Normal rendering: display the values of the normals. */
	if (object.renderMode == 1) {
		frag_color = testNormals();
	}
}