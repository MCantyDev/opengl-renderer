#include "mesh/Cube.h"

Cube::Cube()
{
	generateMesh();
}

void Cube::generateMesh()
{
	mesh = Mesh(vertices, indices, "default");
}