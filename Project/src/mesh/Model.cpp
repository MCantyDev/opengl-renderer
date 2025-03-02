#include "mesh/Model.h"

Model::Model(int ID, std::vector<Mesh> m)
	: Object(ID), meshes(m)
{
	std::cout << "Functional: Model Loaded Successfully" << std::endl;
}

void Model::draw(std::shared_ptr<Shader> s, ShaderType t)
{
	s->use();
	updateMatrix();
	s->setMat4("model", modelMatrix);

	for (auto& mesh : meshes)
	{
		mesh.draw(s, t);
	}
}