#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include <memory>

// To stop the circular reference when including Object, Im using Forward Declaration.
class Object;

enum LightType
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class Light
{
public:
	Light() = default;
	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, std::shared_ptr<Object> mesh, LightType type);

	virtual ~Light() = default;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	std::shared_ptr<Object> mesh;
	LightType type;
};

#endif // LIGHT_H