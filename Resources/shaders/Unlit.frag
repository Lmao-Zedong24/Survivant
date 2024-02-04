#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D u_diffuse;

void main()
{
	vec4 texColor = texture(u_diffuse, TexCoords);

	if (texColor.a < 0.001)
	{
		discard;
		return;
	}

	FragColor = texColor;
}