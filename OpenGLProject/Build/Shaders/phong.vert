#version 430 core

layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec3 vs_normal;
layout (location = 2) in vec2 vs_texcoord;

out vec3 fs_position;
out vec3 fs_normal;
out vec2 fs_texcoord;

uniform mat4 mvp;
uniform mat4 model_view;

void main()
{
	fs_normal = normalize(mat3(model_view) * vs_normal);
	fs_position = vec3(model_view * vec4(vs_position, 1));
	fs_texcoord = vs_texcoord;

	gl_Position = mvp * vec4(vs_position, 1.0);
}