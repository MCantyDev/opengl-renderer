#include "mesh/Primitive.h"

void Primitive::setPosition(glm::vec3 coordinates)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), coordinates);
}

void Primitive::setRotation(float angle, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Primitive::setScale(glm::vec3 scaler)
{
	modelMatrix = glm::scale(modelMatrix, scaler);
}

void Primitive::linkToVAO(VBO& vbo)
{
	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, (8 * sizeof(float)), (void*)0);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, (8 * sizeof(float)), (void*)(3 * sizeof(float)));
	vao.linkAttrib(vbo, 2, 2, GL_FLOAT, (8 * sizeof(float)), (void*)(6 * sizeof(float)));
}