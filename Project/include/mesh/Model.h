#ifndef MODEL_H
#define MODEL_H

#include "mesh/Mesh.h"

#include "shaders/Shader.h"

#include <iostream>
#include <vector>

class Model
{
public:
	Model(std::vector<Mesh> m);

	void draw(Shader& s);

private:
	std::vector<Mesh> meshes;
};

#endif // MODEL_H