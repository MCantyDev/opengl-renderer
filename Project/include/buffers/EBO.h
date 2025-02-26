#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <vector>

class EBO
{
public:
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO() = default;
	EBO(std::vector<GLuint> indices);
	
	~EBO() = default;

	void bind();   // Binds the EBO
	void unbind(); // Unbinds the EBO
	void clear(); // Deletes the EBO

	GLuint getID(); // Get the ID

private:
	// ID reference of Elements Buffer Object
	GLuint ID;
};

#endif