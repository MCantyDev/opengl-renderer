#ifndef MATERIAL_H
#define MATERIAL_H

#include "glad/glad.h"
#include "material/Base.h"

#include <string>

struct Material
{
	Material(); // Default Constructor

	Material(const Base& base, float shininess);
	Material(GLuint diffuse, GLuint specular, GLuint emission, float shininess);
	
	Base base;
	bool useTexture;

	GLuint diffuseTexture;
	GLuint specularTexture;
	GLuint emissionTexture;

	float shininess;

};

#endif // MATERIAL_H