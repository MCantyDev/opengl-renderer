#version 460 core

// Output from Shader
out vec4 FragColour;

// Taking values from Vertex Shader
in vec3 normal;
in vec3 fragPos;
in vec2 textureCoords;

#define MAX_DIRECTIONAL 5
#define MAX_POINTLIGHT 20
#define MAX_SPOTLIGHT 20

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

// Different types of light
// Direction Light (e.g. The Sun!)
struct DirLight 
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Point Light (e.g. Standard Light bulb)
struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// Spot Light (e.g. A Flashlight)
struct SpotLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic; 

	float innerCutOff;
	float outerCutOff;
};

uniform vec3 viewPos; // Camera's Position (View Matrix)

uniform DirLight dirLights[MAX_DIRECTIONAL];
uniform PointLight pointLights[MAX_POINTLIGHT];
uniform SpotLight spotLights[MAX_SPOTLIGHT];

uniform int numDirLights;
uniform int numPointLights;
uniform int numSpotLights;

uniform bool useTexture; 
uniform Material material; // Material

vec3 calcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightDir = normalize(-light.direction);
	// Diffuse Lighting
	float diff = max(dot(normal, lightDir), 0.0);
	// specular Lighting
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


	// Work out lighting
	if (useTexture)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, textureCoords));
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, textureCoords));
		specular = light.specular * spec * vec3(texture(material.specular, textureCoords).r);
	}
	else
	{
		ambient = light.ambient * material.base.ambient;
		diffuse = light.diffuse * diff * material.base.diffuse;
		specular = light.specular * spec * material.base.specular;
	}

	return (ambient + diffuse + specular) ;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 lightDir = normalize(light.position - fragPos);
	// Diffuse Lighting
	float diff = max(dot(normal, lightDir), 0.0);
	// Specular Lighting
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	if (useTexture)
	{
		ambient = light.ambient * vec3(texture(material.diffuse, textureCoords));
		diffuse = light.diffuse * diff * vec3(texture(material.diffuse, textureCoords));
		specular = light.specular * spec * vec3(texture(material.specular, textureCoords).r);
	}
	else
	{
		ambient = light.ambient * material.base.ambient;
		diffuse = light.diffuse * diff * material.base.diffuse;
		specular = light.specular * spec * material.base.specular;
	}
	return ambient + attenuation * (diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    // Compute smooth spotlight effect
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    if (theta > light.outerCutOff)
    {
        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        
        // Specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        // Attenuation (based on distance)
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        if (useTexture)
        {
            vec3 diffuseTex = vec3(texture(material.diffuse, textureCoords));
            vec3 specularTex = vec3(texture(material.specular, textureCoords).r);

            ambient = light.ambient * diffuseTex;
            diffuse = light.diffuse * diff * diffuseTex;
            specular = light.specular * spec * specularTex;
        }
        else
        {
            ambient = light.ambient * material.base.ambient;
            diffuse = light.diffuse * diff * material.base.diffuse;
            specular = light.specular * spec * material.base.specular;
        }

        // Apply attenuation and spotlight intensity
        ambient *= attenuation;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
    }

    return (ambient + diffuse + specular);
}


void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result;

	for (int i = 0; i < numDirLights; i++)
	{
		result += calcDirectionalLight(dirLights[i], norm, viewDir);
	}

	for (int i = 0; i < numPointLights; i++)
	{
		result += calcPointLight(pointLights[i], norm, fragPos, viewDir);
	}

	for (int i = 0; i < numSpotLights; i++)
	{
		result += calcSpotLight(spotLights[i], norm, fragPos, viewDir);
	}

	if (useTexture)
	{
		result += texture(material.emission, textureCoords).rgb;
	}

	FragColour = vec4(result, 1.0);
};