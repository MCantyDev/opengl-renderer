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
	float shininess;
};

uniform Material material;
uniform bool useTexture;

void main()
{
    FragColor = vec4(material.base.diffuse, 1.0);
};