#include "mesh/Primitive.h"

Primitive::Primitive()
	: Object()
{
}

void Primitive::draw(std::shared_ptr<Shader> s, ShaderType t)
{
	s->use();
	updateMatrix();
	s->setMat4("model", modelMatrix);
	mesh.draw(s, t);
}

void Primitive::setMaterial(std::string materialName)
{
	mesh.materialName = materialName;
}
