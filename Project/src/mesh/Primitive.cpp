#include "mesh/Primitive.h"

Primitive::Primitive()
{
}

void Primitive::draw(Shader& s, ShaderType t)
{
	s.use();
	updateMatrix();
	s.setMat4("model", modelMatrix);
	mesh.draw(s, t);
}
