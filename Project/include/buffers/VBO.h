#ifndef VBO_H
#define VBO_H

#include "glad/glad.h"

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Binds the VBO
	void bind();
	// Unbinds the VBO
	void unbind();
	// Deletes the VBO
	void clear();

	GLuint getID();

private:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
};

#endif // VBO_H