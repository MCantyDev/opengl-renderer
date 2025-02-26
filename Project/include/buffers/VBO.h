#ifndef VBO_H
#define VBO_H

#include "glad/glad.h"

#include "Structures.h"

#include <vector>

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO() = default;
	VBO(std::vector<Vertex> vertices);

	~VBO() = default;

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