#include "material/Material.h"


// Custom Constructors for Material
Material::Material()
	: base(), shininess(32.0f), useTexture(false)
{

}

Material::Material(const Base& base, float shininess)
	: base(base), shininess(shininess), useTexture(false)
{

}

Material::Material(GLuint diffuse, GLuint specular, GLuint emission, float shininess)
	: base(), diffuseTexture(diffuse), specularTexture(specular), emissionTexture(emission), shininess(shininess), useTexture(true)
{

}