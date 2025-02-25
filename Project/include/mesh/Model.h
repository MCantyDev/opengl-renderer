#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "shaders/Shader.h"
#include "mesh/mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map> 
#include <vector>


class Model
{
public:
	Model(const char* p);

	void draw(Shader& s);

private:
	std::vector<Mesh> meshes;
	std::vector<Text> texturesLoaded;

	std::string directory;

	void loadModel(std::string p);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	GLuint TextureFromFile(const char* path, const std::string& directory);

	std::vector<Text> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

#endif // MODEL_H