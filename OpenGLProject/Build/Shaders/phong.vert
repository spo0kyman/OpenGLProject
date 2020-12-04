#version 430 core

layout (location = 0) in vec3 vs_position;
layout (location = 1) in vec3 vs_normal;

out vec3 fs_position;
out vec3 fs_normal;

uniform mat4 mvp;
uniform mat4 model_view;

void main()
{
	fs_normal = normalize(mat3(model_view) * vs_normal);
	fs_position = vec3(model_view * vec4(vs_position, 1));

	gl_Position = mvp * vec4(vs_position, 1.0);
}