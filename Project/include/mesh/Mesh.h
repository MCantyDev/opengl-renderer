#ifndef MESH_H
#define MESH_H

#include "shaders/Shader.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

/*
* @class Mesh
* @brief Abstract class created for Meshes that allows you to scale and draw the Meshes as wanted. Gives a standard Virtual draw function to be created
* @notes Mesh Class creates the VAO and modelMatrix of the Object as these 2 elements are able to be created without any identifiers
*/
class Mesh
{
public:
	Mesh() = default;

	void setPosition(glm::vec3 coordinates);
	void setRotation(float angle, glm::vec3 axis);
	void setScale(glm::vec3 scaler);

	virtual void draw(Shader& shader) = 0;

protected:
	VAO meshVAO;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	void linkToVAO(VBO& vbo);
};

#endif // MESH_H