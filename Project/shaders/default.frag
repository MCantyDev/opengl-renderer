#version 460 core

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
	BaseMaterial base;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	float shininess;
};

// Structure for the Light that is being shon onto the object
struct Light 
{
	vec3 position; // Position of the Light
	
	vec3 ambient; // The Lights Ambient strength
	vec3 diffuse; // The Lights Diffuse Colour
	vec3 specular; // The Lights Specular Intensity
};

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 textureCoords;

uniform bool useTexture; 
uniform vec3 viewPos; // Camera's Position (View Matrix)
uniform Material material; // Material
uniform Light light; // Light

void main()
{
	// Ambient Lighting
	vec3 ambient;

	// Diffuse Lighting
	vec3 norm = normalize(normal); // Normalising to get Unit Vectors
	vec3 lightDir = normalize(light.position - fragPos); // LightDir is the difference between the light's position and the frag position
	float diff = max(dot(norm, lightDir), 0.0); // Max value -> Either the dot product of the normals or 0
	vec3 diffuse;

	// Specular Lighting
	vec3 viewDir = normalize(viewPos - fragPos); // Getting the direction the camera is looking
	vec3 reflectDir = reflect(-lightDir, norm); // simulating \ / (by inversing the light direction based on our unit vector normals "\" we get "/"
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // retreiving higher val from (dot product of viewdir and reflectdir) or 0. Then raising it by the power of our materials shininess
	vec3 specular;

	// Result
	vec3 result;
	
	if (useTexture)
	{
		ambient = light.ambient * vec3(texture(material.diffuseTexture, textureCoords)).rgb;
		diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture, textureCoords)).rgb;
		specular = light.specular * spec * vec3(texture(material.specularTexture, textureCoords)).rgb;
		result = (ambient + diffuse + specular);
	}
	else
	{
		ambient = light.ambient * material.base.ambient;
		ambient = clamp(ambient, 0.0, 1.0);

		diffuse = (diff * material.base.diffuse) * light.diffuse; // calculating the diffuse
		specular = (spec * material.base.specular) * light.specular; // Calculating the specular component
		result = (ambient + diffuse + specular); // The resulting Vec3 is all our vec3's added together
	}
	
	FragColor =  vec4(clamp(result, 0.0, 1.0), 1.0); // Outputting our Objects Diffuse Colour
};