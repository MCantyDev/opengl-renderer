#include "core/MaterialManager.h"

// Defining Instance
MaterialManager* MaterialManager::instance = nullptr;

MaterialManager::MaterialManager()
{
	std::cout << "Setup: Material Manager created" << std::endl;
}

MaterialManager::~MaterialManager()
{
	textureManager->DestroyInstance();
	std::cout << "Closing: Material Manager destroyed" << std::endl;
}

MaterialManager* MaterialManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MaterialManager();
	}
	return instance;
}

void MaterialManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

std::shared_ptr<Material> MaterialManager::getMaterial(const char* materialName)
{
	auto it = materialMap.find(materialName);

	if (it != materialMap.end())
	{
		return std::make_shared<Material>(it->second);
	}
	return nullptr;
}

void MaterialManager::addMaterial(const char* materialName, const Material& material)
{
	materialMap[materialName] = material;
	std::cout << "Functional: Adding Material to Material Manager - Name: \"" << materialName << "\"" << std::endl;
}

void MaterialManager::deleteMaterial(const char* materialName)
{
	materialMap.erase(materialName);
	std::cout << "Functional: Removing Material from Material Manager - Name: \"" << materialName << "\"" << std::endl;
}

void MaterialManager::changeMaterialTexture(const char* materialName, const char* textureName, TextureType textureType)
{
	auto materialIt = materialMap.find(materialName);

	if (materialIt != materialMap.end())
	{
		Material* material = &materialIt->second;
		GLuint textureID = textureManager->getTexture(textureName, textureType);

		switch (textureType)
		{
			case TEXTURE_DIFFUSE:
				material->diffuseTexture = textureID;
		
			case TEXTURE_SPECULAR:
				material->specularTexture = textureID;
		
			case TEXTURE_EMISSION:
				material->emissionTexture = textureID;

			default:
				std::cout << "Functional Error: Texture type does not exist" << std::endl;
		}
	}
}