#version 450 core

in vec3 Coord;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	FragColor = vec4(Coord, 1.0f);
}
