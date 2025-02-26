#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

// OpenGL Include
#include "glad/glad.h"
#include "glm/glm.hpp"

// Assimp Include
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// Core Functionality Include
#include "core/MaterialManager.h"
#include "core/TextureManager.h"
#include "shaders/Shader.h"

#include "mesh/Mesh.h"

// Standard Library Include 
#include <string>
#include <iostream>
#include <vector>

class AssimpLoader
{
public:
	AssimpLoader();
	~AssimpLoader();

	std::vector<Mesh> load(std::string path, bool flipped = false); // Default is False

private:
	std::string directory;
	bool flippedOnLoad;

	MaterialManager* materialManager = MaterialManager::GetInstance();
	TextureManager* textureManager = TextureManager::GetInstance();

	void processNode(aiNode * node, const aiScene * scene, std::vector<Mesh>& meshes);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::string processTexturesIntoMaterial(aiMaterial* mat);

	std::vector<Vertex> processVertex(aiMesh* mesh);
	std::vector<GLuint> processIndices(aiMesh* mesh);
};

#endif // ASSIMPLOADER_H