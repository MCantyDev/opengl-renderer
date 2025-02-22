#ifndef BASE_H
#define BASE_H

#include "glm/glm.hpp"

struct Base
{
	Base(); // Default Constructor that just sets some default values so the model isnt just "PURE black"
	Base(glm::vec3 a, glm::vec3 d, glm::vec3 s); // Overriden constructor to give the Base some different initial values

	~Base() = default; // Default Destructor

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

#endif // BASEMATERIAL_H