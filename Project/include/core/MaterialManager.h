#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <unordered_map>
#include <iostream>

#include "core/TextureManager.h"
#include "material/Material.h"

// Singleton
class MaterialManager
{
public:
	static MaterialManager* GetInstance();
	static void DeleteInstance();

	~MaterialManager();

	Material* getMaterial(const char* materialName);

	void addMaterial(const char* materialName, const Material& material);
	void deleteMaterial(const char* materialName);
	void changeMaterialTexture(const char* materialName, const char* textureName, TextureType textureType);

private:
	MaterialManager();
	static MaterialManager* instance;
	TextureManager* textureManager = TextureManager::GetInstance();

	// Map of Materials
	std::unordered_map<std::string, Material> materialMap;

	MaterialManager(const MaterialManager&) = delete;
	MaterialManager& operator=(const MaterialManager&) = delete;

	MaterialManager(MaterialManager&&) = delete;
	MaterialManager& operator=(MaterialManager&&) = delete;
};

#endif // MATERIALMANAGER_H