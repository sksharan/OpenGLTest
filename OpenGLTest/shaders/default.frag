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

/* Represents a directional light. */
struct DirectionalLight {
    /* Direction of this light */
    vec3 direction;
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
uniform DirectionalLight dLights[2];   //corresponds to MAX_DIRECTIONAL_LIGHTS in Constants.h

/* Number of lights currently in use. */
uniform int numPLights;               //should not exceed length of pLights
uniform int numDLights;               //should not exceed length of dLights

/* Sampler for the object's base texture. */
uniform sampler2D texture0;

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

/* Output values. */
out vec4 frag_color;

/* Test for point light. See http://antongerdelan.net/opengl/phong.html
for more details. */
vec3 pointLightTestWithPhong() {
    //Light constants
    vec4 light_pos_world = vec4(0, 0, 50, 1);
    vec4 light_pos_eye = viewMatrix * light_pos_world;
    vec3 La = vec3(0.2, 0.2, 0.2);
    vec3 Ld = vec3(0.7, 0.7, 0.7);
    vec3 Ls = vec3(1.0, 1.0, 1.0);

    //Object constants
    vec3 Ka = vec3(1.0, 1.0, 1.0);
    vec3 Kd = vec3(1.0, 0.5, 0.0);
    vec3 Ks = vec3(1.0, 1.0, 1.0);
    float shininess = 50.0;

    //ambient term
    vec3 Ia = La * Ka;

    //diffuse term
    vec3 direction_to_light_eye = normalize( vec3(light_pos_eye - f_eye_position) );
    vec3 Id = Ld * Kd * max( dot(direction_to_light_eye, f_eye_normal), 0.0 );

    //specular term
    vec3 reflection_eye = reflect(-direction_to_light_eye, f_eye_normal);
    vec3 direction_to_viewer_eye = normalize( -vec3(f_eye_position) );  //can do this since we're working in eye space
    float specular_dot_prod = max( dot(reflection_eye, direction_to_viewer_eye), 0.0 );
    vec3 Is = Ls * Ks * pow(specular_dot_prod, shininess);

    return Ia + Id + Is;
}

/* Test the value of the normals. Right-facing parts are red, upward-facing
parts are green, and forward-facing parts are blue. Any negative values are
clamped to 0. See http://antongerdelan.net/opengl/debugshaders.html for more details. */
vec4 testNormals() {
    return vec4(f_eye_normal, 1.0); 
}

/* Uses the Phong lighting equation to calculate the color of this fragment as if
pLights[id] is the only light in the scene. */
vec3 phongForPointLight(int id) {
    vec4 light_pos_eye = viewMatrix * vec4(pLights[id].position, 1.0);  //move light position into eye space

    //ambient term
    vec3 Ia = pLights[id].La * object.Ka;

    //diffuse term
    vec3 direction_to_light_eye = normalize( vec3(light_pos_eye - f_eye_position) );
    vec3 Id = pLights[id].Ld * object.Kd * max( dot(direction_to_light_eye, f_eye_normal), 0.0 );
    float texture_weight = 0.9;
    Id = (1 - texture_weight) * Id + texture_weight * vec3(texture(texture0, f_texcoord));  //texture contributes to diffuse component

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
    /* Textured rendering: if lighting is enabled, include the lighting calculations, otherwise
     * only use the texture. */
    if (object.renderMode == 0) {
        if (object.light_enabled == 1) {
            vec3 rgb_color = vec3(0, 0, 0);
            for (int id = 0; id < numPLights; id++) {
                rgb_color += phongForPointLight(id);
            }
            frag_color = vec4(rgb_color, texture(texture0, f_texcoord).a);

        } else {
            frag_color = texture(texture0, f_texcoord);
        }
    }

    /* Normal rendering: display the values of the normals. */
    if (object.renderMode == 1) {
        frag_color = testNormals();
    }
}