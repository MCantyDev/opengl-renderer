#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "lighting/Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight() = default;
	DirectionalLight(glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s);

	glm::vec3 direction;
};

#endif // DIRECTIONALLIGHT_H