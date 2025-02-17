#include "buffers/VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
	: ID(0)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::clear()
{
	glDeleteBuffers(1, &ID);
}

GLuint VBO::getID()
{
	return ID;
}