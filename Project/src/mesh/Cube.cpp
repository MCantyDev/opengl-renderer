#include "mesh/Cube.h"

Cube::Cube()
{
	cubeVAO.bind();
	cubeVBO = VBO(vertices.data(), (vertices.size() * sizeof(GLfloat)));

	cubeVAO.linkAttrib(cubeVBO, 0, 3, GL_FLOAT, (8 * sizeof(float)), (void*)0);
	cubeVAO.linkAttrib(cubeVBO, 1, 3, GL_FLOAT, (8 * sizeof(float)), (void*)(3 * sizeof(float)));
	cubeVAO.linkAttrib(cubeVBO, 2, 2, GL_FLOAT, (8 * sizeof(float)), (void*)(6 * sizeof(float)));

	cubeVAO.unbind();
	cubeVBO.unbind();
}

void Cube::setPosition(glm::vec3 coordinates)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), coordinates);
}

void Cube::setRotation(float angle, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Cube::setScale(glm::vec3 scaler)
{
	modelMatrix = glm::scale(modelMatrix, scaler);
}

void Cube::draw(Shader& shader)
{
	shader.use();
	shader.setMat4("model", modelMatrix);

	cubeVAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	cubeVAO.unbind();
}