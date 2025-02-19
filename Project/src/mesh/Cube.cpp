#include "mesh/Cube.h"

Cube::Cube()
{
	cubeVAO.bind();
	cubeVBO = VBO(vertices, sizeof(vertices));

	cubeVAO.linkAttrib(cubeVBO, 0, 3, GL_FLOAT, (5 * sizeof(float)), (void*)0);
	cubeVAO.linkAttrib(cubeVBO, 1, 2, GL_FLOAT, (5 * sizeof(float)), (void*)(3 * sizeof(float)));

	cubeVAO.unbind();
	cubeVBO.unbind();
}

void Cube::setPosition(float x, float y, float z)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void Cube::setRotation(float angle, glm::vec3 axis)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);
}

void Cube::draw(Shader& shader)
{
	shader.use();
	shader.setMat4("model", modelMatrix);

	cubeVAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	cubeVAO.unbind();
}