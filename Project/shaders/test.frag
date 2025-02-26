#version 460 core

// Output from Shader
out vec4 FragColour;

// Taking values from Vertex Shader
in vec3 normal;
in vec3 fragPos;
in vec2 textureCoords;

// Structure for Base Material (An Object with no Texture)
struct BaseMaterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Structure for Material (An Object with Texture)
struct Material 
{
	BaseMaterial base; // Base Material so static values can be used

	sampler2D diffuse; // Diffuse Map
	sampler2D specular; // Specular Map
	sampler2D emission; // Emission Map

	float shininess;
};

uniform bool useTexture; 
uniform Material material; // Material

void main()
{
	vec3 diffuseColour;
	vec3 specularColour;
	vec3 emissionColour;

	if (useTexture)
	{
		diffuseColour = texture(material.diffuse, textureCoords).rgb;
		specularColour = texture(material.specular, textureCoords).rgb;
		emissionColour = texture(material.emission, textureCoords).rgb;
	}

	vec3 result = (diffuseColour + specularColour + emissionColour);

	FragColour = vec4(result, 1.0);
};