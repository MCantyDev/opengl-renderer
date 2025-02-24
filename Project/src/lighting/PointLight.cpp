#include "lighting/PointLight.h"

PointLight::PointLight(glm::vec3 pos, glm::vec3 a, glm::vec3 d, glm::vec3 s, float c, float l, float q)
	: Light(a, d, s), position(pos), constant(c), linear(l), quadratic(q) 
{

}