#include "mesh/Primitive.h"

Primitive::Primitive(int ID)
	: Object(ID)
{
}

void Primitive::draw(std::shared_ptr<Shader> s, ShaderType t)
{
	s->use();
	updateMatrix();
	s->setMat4("model", modelMatrix);
	mesh.draw(s, t);
}
