#version 460 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 colour;
uniform vec3 lightColour;

void main()
{
	// Ambient Lighting
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	// Diffuse Lighting
	vec3 norm = normalize(normal); // Normalising to get Unit Vectors
	vec3 lightDir = normalize(lightPos - fragPos); // LightDir is the difference between the light's position and the frag position
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	// Specular Lighting
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec3 specular = specularStrength * spec * lightColour;

	// Result
	vec3 result = (ambient + diffuse + specular) * colour;
	FragColor =  vec4(result, 1.0);
};