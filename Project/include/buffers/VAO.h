#ifndef VAO_H
#define VAO_H

#include "glad/glad.h"
#include "VBO.h"

/*
* @class VAO
* @brief This class creates a VAO object with all required functions for use
*/
class VAO
{
public:
	/*
	* The Constructor which takes in no params, generates a VAO object in which a VBO can be linked
	* 
	* @brief Constructor for VAO - Vertex Array Object
	* @param NONE
	*/
	VAO();

	/*
	* @brief Link an Attribute Pointer to the VAO
	* @param VBO& VBO - The VBO which you want to link
	* @param GLuint layout - The layout location to bind the attribute
	* @param GLint size - Number of values per cluster (e.g., 3 for a position with x, y, z)
	* @param GLsizei stride - Distance between consecutive attributes (in bytes)
	* @param const void* pointer - Offset of the first component of the attribute
	*/
	void linkAttrib(VBO& VBO, GLuint layout, GLint size, GLsizei stride, const void* pointer);

	/*
	* Bind the VAO to be used within the program
	* 
	* @brief Bind the VAO
	* @param NONE
	* 
	*/
	void bind();

	/*
	* Unbind the active VAO - Sets value to 0
	* 
	* @brief Unbind the VAO
	* @param NONE
	*/
	void unbind();

	/*
	* @brief Clean up for the VAO, removes all data
	* 
	* @param NONE
	*/
	void clear();

	/*
	* @brief Return the ID of the VAO
	* @param NONE
	* @return GLuint ID - ID of the VAO
	*/
	GLuint getID();

private:
	GLuint ID; // ID for the Vertex Array Object
};

#endif // VAO_H