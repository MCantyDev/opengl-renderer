#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

class Light
{
public:
	Light() = default;
	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s);

	virtual ~Light() = default;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

#endif // LIGHT_H