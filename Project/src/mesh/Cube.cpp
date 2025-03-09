#include "mesh/Cube.h"

Cube::Cube()
	: Primitive()
{
	generateMesh();
}

void Cube::generateMesh()
{
	mesh = Mesh(std::vector<Vertex>(vertices), std::vector<unsigned int>(indices), "default");
}