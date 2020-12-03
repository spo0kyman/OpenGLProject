#version 430 core

in vec3 fs_color;
in vec2 fs_uv;

out vec4 out_color;

uniform sampler2D baseTexture;

void main()
{
    //out_color = vec4(fs_color, 1.0);
    out_color = texture(baseTexture, fs_uv);
}