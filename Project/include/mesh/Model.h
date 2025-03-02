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
	Model(int ID, std::vector<Mesh> m);

	virtual void draw(std::shared_ptr<Shader> s, ShaderType t = SHADER_DEFAULT) override;

private:
	std::vector<Mesh> meshes;
};

#endif // MODEL_H