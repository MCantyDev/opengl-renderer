#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "shaders/Shader.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"

#include "mesh/Object.h"

/*
* @class Primitive
* @brief Abstract class created for primitives that allows you to scale and draw the primitives as wanted. Gives a standard Virtual draw function to be created.
* Primitive Class creates the VAO and modelMatrix of the Object as these 2 elements are able to be created without any identifiers
*/
class Primitive
{
public:
	Primitive() = default;

	void setPosition(glm::vec3 coordinates);
	void setRotation(float angle, glm::vec3 axis);
	void setScale(glm::vec3 scaler);

	virtual void draw(Shader& shader) = 0;

protected:
	VAO vao;
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	void linkToVAO(VBO& vbo);
};

#endif // PRIMITIVE