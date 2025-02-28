#include "mesh/Model.h"

Model::Model(std::vector<Mesh> m)
	: meshes(m)
{
	std::cout << "Functional: Model Loaded Successfully" << std::endl;
}

void Model::draw(Shader& s, ShaderType t)
{
	s.use();
	updateMatrix();
	s.setMat4("model", modelMatrix);

	for (auto& mesh : meshes)
	{
		mesh.draw(s, t);
	}
}