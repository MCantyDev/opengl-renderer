#include "mesh/Model.h"

Model::Model(std::vector<Mesh> m)
	: Object(), meshes(m)
{
	std::cout << "Functional: Model Loaded Successfully" << std::endl;
}

Model::Model(const Model& other)
	: Object(), meshes(other.meshes) {
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

void Model::setMaterial(std::string materialName)
{
	if (materialName == currentMaterial) return;

	for (auto& mesh : meshes)
	{
		mesh.materialName = materialName;
	}
	currentMaterial = materialName;
}

std::shared_ptr<Model> Model::clone() const
{
	return std::make_shared<Model>(*this);
}