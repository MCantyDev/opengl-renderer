#include "core/AssimpLoader.h"

AssimpLoader::AssimpLoader()
	: flippedOnLoad(false)
{
	std::cout << "Setup: Assimp Loader created" << std::endl;
}

AssimpLoader::~AssimpLoader()
{
	std::cout << "Closing: Assimp Loader destroyed" << std::endl;
}

std::vector<Mesh> AssimpLoader::load(std::string path, bool flipped)
{
	flippedOnLoad = flipped; // Adjust Flipped on be correct

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ValidateDataStructure);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Functional Error: Assimp Load Failed - " << importer.GetErrorString() << std::endl;
		return {};
	}

	directory = path.substr(0, path.find_last_of('/') + 1); // Work out the directory by finding the last /
	
	std::vector<Mesh> meshes;
	processNode(scene->mRootNode, scene, meshes);

	return meshes;
}

void AssimpLoader::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshes)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	
	// Recursive call to travel through the Tree
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshes);
	}
}

Mesh AssimpLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices = processVertex(mesh);
	std::vector<GLuint> indices = processIndices(mesh);
	std::string materialName = "default";

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		materialName = processTexturesIntoMaterial(mat);
	}

	return Mesh(vertices, indices, materialName);
}

std::vector<Vertex> AssimpLoader::processVertex(aiMesh* mesh)
{
	std::vector<Vertex> vertices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;
		// Positional Data
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		// Normal Data
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.textureCoords = vec;
		}
		else
		{
			vertex.textureCoords = glm::vec2(0.0f);
		}
		vertices.push_back(vertex);
	}
	return vertices;
}

std::vector<GLuint> AssimpLoader::processIndices(aiMesh* mesh)
{
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	return indices;
}

std::string AssimpLoader::processTexturesIntoMaterial(aiMaterial* mat)
{
	std::string materialName = mat->GetName().C_Str();

	// Check if the Material Exists within the Material Map
	std::shared_ptr<Material> existingMaterial = materialManager->getMaterial(materialName.c_str());
	if (existingMaterial != nullptr)
	{
		return materialName;
	}

	aiString textureName;
	GLuint diffuseTexture = 0, specularTexture = 0, emissionTexture = 0;

	// Load diffuse texture if available
	if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0 && mat->GetTexture(aiTextureType_DIFFUSE, 0, &textureName) == AI_SUCCESS)
	{
		diffuseTexture = textureManager->addTexture(textureName.C_Str(), TEXTURE_DIFFUSE, (directory + textureName.C_Str()).c_str(), flippedOnLoad);
	}

	// Load specular texture if available
	if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0 && mat->GetTexture(aiTextureType_SPECULAR, 0, &textureName) == AI_SUCCESS)
	{
		specularTexture = textureManager->addTexture(textureName.C_Str(), TEXTURE_SPECULAR, (directory + textureName.C_Str()).c_str(), flippedOnLoad);
	}

	// Load emission texture if available
	if (mat->GetTextureCount(aiTextureType_EMISSIVE) > 0 && mat->GetTexture(aiTextureType_EMISSIVE, 0, &textureName) == AI_SUCCESS)
	{
		emissionTexture = textureManager->addTexture(textureName.C_Str(), TEXTURE_EMISSION, (directory + textureName.C_Str()).c_str(), flippedOnLoad);
	}

	// Create new material and store it in the MaterialManager
	materialManager->addMaterial(materialName.c_str(), std::make_shared<Material>(diffuseTexture, specularTexture, emissionTexture, 32.0f));
	return materialName;
}