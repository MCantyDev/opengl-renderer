#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "glad/glad.h"

#include "glm/glm.hpp"

#include <string>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

#endif // STRUCTURES_H