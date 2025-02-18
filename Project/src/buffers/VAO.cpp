#include "buffers/VAO.h"

VAO::VAO()
	: ID(0)
{
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset)
{
	VBO.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbind();
}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::clear()
{
	glDeleteVertexArrays(1, &ID);
}


GLuint VAO::getID()
{
	return ID;
}