#include "mesh/Cube.h"

Cube::Cube(int ID)
	: Primitive(ID)
{
	generateMesh();
}

void Cube::generateMesh()
{
	mesh = Mesh(vertices, indices, "default");
}