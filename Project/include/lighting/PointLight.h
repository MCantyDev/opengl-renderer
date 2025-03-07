#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lighting/Light.h"

class PointLight : public Light
{
public:
	PointLight() = default;
	PointLight(glm::vec3 pos, glm::vec3 a, glm::vec3 d, glm::vec3 s, float c, float l, float q, std::shared_ptr<Object> mesh = nullptr);

	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;
};

#endif // POINTLIGHT_H