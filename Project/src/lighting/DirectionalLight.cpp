#include "lighting/DirectionalLight.h"

// Doesnt need to send through a Mesh as Directional Lights USUALLY dont have Meshes regardless
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 a, glm::vec3 d, glm::vec3 s)
	: Light(a, d, s, nullptr), direction(dir) 
{

}