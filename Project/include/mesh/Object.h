#ifndef OBJECT_H
#define OBJECT_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_precision.hpp"

#include "shaders/Shader.h"

struct Rotation
{
	float rotation;
	glm::vec3 axis;
};

class Object
{
public:
	Object()
		: modelMatrix(glm::mat4(1.0f)), position(glm::vec3(0.0f)), 
		scale(glm::vec3(1.0f)), rotation(0.0f), axis(glm::vec3(1.0f)) {};

	virtual ~Object() = default;

	virtual void draw(std::shared_ptr<Shader> s, ShaderType t = SHADER_DEFAULT) = 0;
	virtual void setMaterial(std::string materialName) = 0;

	void setPosition(glm::vec3 p) 
	{ 
		position = p;  
	}

	void setRotation(float d, glm::vec3 a) 
	{
		rotation = d;
		axis = a; 
	}

	void setScale(glm::vec3 s) 
	{ 
		scale = s;
	}

	glm::vec3 getPosition()
	{
		return position;
	}
	glm::vec3 getAxis()
	{
		return axis;
	}
	float getRotation()
	{
		return rotation;
	}
	glm::vec3 getScale()
	{
		return scale;
	}

	int id = -1; // To be Set by ObjectManager when added to ObjectMap
	std::string name;

protected:
	glm::mat4 modelMatrix;
	glm::vec3 position, scale, axis;
	float rotation;

	void updateMatrix()
	{
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::scale(modelMatrix, scale);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), axis);
	}
};

#endif // OBJECT_H