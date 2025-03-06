#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include <memory>

// To stop the circular reference when including Object, Im using Forward Declaration.
class Object;

class Light
{
public:
	Light() = default;
	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, std::shared_ptr<Object> mesh);

	virtual ~Light() = default;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	std::shared_ptr<Object> mesh;
};

#endif // LIGHT_H