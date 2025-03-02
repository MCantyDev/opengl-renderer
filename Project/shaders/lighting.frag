#version 460 core

out vec4 FragColor;

in vec2 textureCoords;

struct BaseMaterial
{
	vec3 diffuse;
};

struct Material 
{
	BaseMaterial base;
};

uniform Material material;

void main()
{
	vec3 result;

	result += material.base.diffuse;

    FragColor = vec4(result, 1.0);
};