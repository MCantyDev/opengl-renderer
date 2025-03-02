#include "lighting/SpotLight.h"

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s, float c, float l, float q, float iC, float oC)
	: Light(a, d, s), position(pos), direction(dir), constant(c), linear(l), quadratic(q), innerCutOff(iC), outerCutOff(oC)
{

}