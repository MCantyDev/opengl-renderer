#include "mesh/Cube.h"

Cube::Cube()
{
	vao.bind();
	vbo = VBO(vertices);

	linkToVAO(vbo);

	vao.unbind();
	vbo.unbind();
}

void Cube::draw(Shader& s)
{
	s.use();
	s.setMat4("model", modelMatrix);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	vao.unbind();
}