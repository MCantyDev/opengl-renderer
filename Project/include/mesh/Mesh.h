#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "shaders/Shader.h"

#include <string>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

struct Text
{
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Text> textures;

	Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::vector<Text> t);
	void draw(Shader& s);

private:
	GLuint VAO, VBO, EBO;

	void setupMesh();
};

#endif // MESH_H