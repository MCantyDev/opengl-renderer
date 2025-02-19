#include "mesh/Mesh.h"

void Mesh::setPosition(glm::vec3 coordinates)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), coordinates);
}

void Mesh::setRotation(float angle, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Mesh::setScale(glm::vec3 scaler)
{
	modelMatrix = glm::scale(modelMatrix, scaler);
}


void Mesh::linkToVAO(VBO& vbo)
{
	meshVAO.linkAttrib(vbo, 0, 3, GL_FLOAT, (8 * sizeof(float)), (void*)0);
	meshVAO.linkAttrib(vbo, 1, 3, GL_FLOAT, (8 * sizeof(float)), (void*)(3 * sizeof(float)));
	meshVAO.linkAttrib(vbo, 2, 2, GL_FLOAT, (8 * sizeof(float)), (void*)(6 * sizeof(float)));
}