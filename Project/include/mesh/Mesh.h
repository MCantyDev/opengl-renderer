#ifndef MESH_H
#define MESH_H

// OpenGL Include
#include "glad/glad.h"
#include "glm/glm.hpp"

// Core Functionality Include
#include "core/MaterialManager.h"
#include "shaders/Shader.h"

// Buffer Include
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"

// Standard Library Include
#include <string>
#include <iostream>
#include <vector>

#include "Structures.h"

class Mesh
{
public:
	std::vector<GLuint> indices; // Indices need to be stored so glDrawElements can reference them
	std::string materialName;

	Mesh() = default; // Default Constrcutor
	Mesh(std::vector<Vertex> v, std::vector<GLuint> i, std::string mName);

	void draw(Shader& s, ShaderType t);

private:
	MaterialManager* materialManager = MaterialManager::GetInstance();

	VAO vao;
	VBO vbo;
	EBO ebo; 
};

#endif // MESH_H