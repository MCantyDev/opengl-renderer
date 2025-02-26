#include "mesh/Model.h"

Model::Model(std::vector<Mesh> m)
	: meshes(m)
{
	std::cout << "Functional: Model Loaded Successfully" << std::endl;
}

void Model::draw(Shader& s)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(s);
	}
}