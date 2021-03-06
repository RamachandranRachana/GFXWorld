#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Coord;
out vec3 Normal;

void main()
{
	gl_Position = vec4(position, 1.0f);
	Coord = position;
	Normal = normal;
}
