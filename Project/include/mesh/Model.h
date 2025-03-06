#ifndef MODEL_H
#define MODEL_H

#include "mesh/Mesh.h"
#include "mesh/Object.h"

#include "shaders/Shader.h"

#include <iostream>
#include <vector>

class Model : public Object
{
public:
	Model(std::vector<Mesh> m);
	Model(const Model& other);

	virtual void draw(std::shared_ptr<Shader> s, ShaderType t = SHADER_DEFAULT) override;
	virtual void setMaterial(std::string materialName) override;

	std::shared_ptr<Model> clone() const;
private:
	std::string currentMaterial; // Currently Meshes only realistically have a single Material anyways
	std::vector<Mesh> meshes;
};

#endif // MODEL_H