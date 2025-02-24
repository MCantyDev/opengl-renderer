#include "lighting/DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s)
	: Light(a, d, s), direction(dir) 
{

}