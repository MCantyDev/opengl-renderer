#include "buffers/VAO.h"

VAO::VAO()
	: ID(0)
{
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLint size, GLsizei stride, const void* pointer)
{
	VBO.bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, pointer);
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