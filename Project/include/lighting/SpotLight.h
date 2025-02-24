#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "lighting/Light.h"

class SpotLight : public Light
{
public:
	SpotLight() = default;
	SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s, float c, float l, float q, float iC, float oC);

	glm::vec3 position;
	glm::vec3 direction;

	float constant;
	float linear;
	float quadratic;
	float outerCutOff;
	float innerCutOff;
};

#endif // SPOTLIGHT_H