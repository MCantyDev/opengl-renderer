#include "mesh/Cube.h"

Cube::Cube()
{
	meshVAO.bind();
	cubeVBO = VBO(vertices.data(), (vertices.size() * sizeof(GLfloat)));

	linkToVAO(cubeVBO);

	meshVAO.unbind();
	cubeVBO.unbind();
}

void Cube::draw(Shader& shader)
{
	shader.use();
	shader.setMat4("model", modelMatrix);

	meshVAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	meshVAO.unbind();
}