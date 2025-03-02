#include "mesh/Mesh.h"

Mesh::Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::string mName)
	: indices(i), materialName(mName)
{
	vao.bind();
	vbo = VBO(v);
	ebo = EBO(i);

	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	vao.linkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
	
	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void Mesh::draw(std::shared_ptr<Shader> s, ShaderType t)
{
	vao.bind();
	
	std::shared_ptr<Material> material = materialManager->getMaterial(materialName.c_str());

	s->setMaterial(material, t);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.unbind();
}