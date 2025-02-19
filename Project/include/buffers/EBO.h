#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO() = default;
	EBO(GLuint* indices, GLsizeiptr size);
	
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