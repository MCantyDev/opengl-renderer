#include "mesh/Cube.h"

Cube::Cube()
{
	vao.bind();
	vbo = VBO(vertices.data(), (vertices.size() * sizeof(GLfloat)));

	linkToVAO(vbo);

	vao.unbind();
	vbo.unbind();
}

void Cube::draw(Shader& shader)
{
	shader.use();
	shader.setMat4("model", modelMatrix);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	vao.unbind();
}