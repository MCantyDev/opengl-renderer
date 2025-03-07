#include "mesh/Cube.h"

Cube::Cube()
	: Primitive()
{
	generateMesh();
}

void Cube::generateMesh()
{
	mesh = Mesh(vertices, indices, "default");
}