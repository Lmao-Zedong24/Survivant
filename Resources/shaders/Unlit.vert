#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 2) in vec2 _texCoords;

out vec2 TexCoords;

uniform mat4 u_mvp;

void main()
{
	gl_Position = u_mvp * vec4(_pos, 1.0);
	TexCoords = _texCoords;
}