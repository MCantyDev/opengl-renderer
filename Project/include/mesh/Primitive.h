#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "shaders/Shader.h"

#include "mesh/Mesh.h"
#include "mesh/Object.h"

/*
* @class Primitive
* @brief Base class created for primitives that allows you to scale and draw the primitives as wanted. Gives a standard draw function to be created.
*/
class Primitive : public Object
{
public:
	Primitive();

	virtual void generateMesh() = 0; // Pure Virtual

	virtual void draw(std::shared_ptr<Shader> s, ShaderType t = SHADER_DEFAULT) override;

protected:
	Mesh mesh;
};

#endif // PRIMITIVE