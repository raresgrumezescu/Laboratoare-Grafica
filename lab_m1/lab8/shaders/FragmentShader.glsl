#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;
uniform int typeOfLight;
uniform float cutOff2;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	int lum = (dot(normalize(N), L) > 0) ? 1:0;
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25;
    float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);
    float specular_light = material_ks * lum;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

	float l = 0.f;

	if (typeOfLight == 1) {
		float cut_off_rad = radians(cutOff2);
		float spot_light = dot(-L, light_direction);
		
		if (spot_light > cos(cut_off_rad)) {	 
			// Quadratic attenuation
			float linear_att = (spot_light - cos(cut_off_rad)) / (1.f - cos(cut_off_rad));
			float light_att_factor = pow(linear_att, 2);
			l = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} else {
			l = ambient_light;  // There is no spot light, but there is light from other objects
		}
	} else {
		float dist	= distance(light_position, world_position);
		float attenuation_factor = 1.f / max(pow(dist, 2), 1.f);
		l = ambient_light + attenuation_factor * (diffuse_light + specular_light);
	}

    // TODO(student): Write pixel out color
	vec3 colour = object_color * l;

    out_color = vec4(colour, 1);

}
