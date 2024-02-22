#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4		u_tint;
uniform sampler2D	u_diffuse;

void main()
{
	FragColor = texture(u_diffuse, TexCoords) * u_tint;
}