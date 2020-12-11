#version 430 core

in vec3 fs_position;
in vec3 fs_normal;
in vec2 fs_texcoord;

out vec4 out_color;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

struct Light{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

uniform sampler2D texture_sample;

void main()
{
	vec3 ambient = material.ambient * light.ambient;

	vec3 direction_to_light = normalize(vec3(light.position) - fs_position);

	float lDotN = max(dot(direction_to_light, fs_normal), 0);
	vec3 diffuse = material.diffuse * light.diffuse * lDotN;

	vec3 specular = vec3(0);

	if(lDotN > 0){
		vec3 direction_to_view = normalize(-fs_position);
		vec3 reflection = reflect(-direction_to_light, fs_normal);
		float intensity = max(dot(direction_to_view, reflection), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * light.specular * intensity;
	}

	out_color = vec4(ambient + diffuse, 1) * texture(texture_sample, fs_texcoord) + vec4(specular, 1);
}