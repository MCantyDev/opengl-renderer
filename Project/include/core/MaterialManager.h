#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <unordered_map>
#include <iostream>

#include "material/Material.h"

// Singleton
class MaterialManager
{
public:
	static MaterialManager* GetInstance();
	static void DeleteInstance();

	~MaterialManager();

	Material* getMaterial(std::string materialName);

	void addMaterial(const Material& material);
	void deleteMaterial(std::string materialName);

private:
	MaterialManager();
	static MaterialManager* instance;

	// Map of Materials
	std::unordered_map<std::string, Material> materialMap;

	MaterialManager(const MaterialManager&) = delete;
	MaterialManager& operator=(const MaterialManager&) = delete;

	MaterialManager(MaterialManager&&) = delete;
	MaterialManager& operator=(MaterialManager&&) = delete;
};

#endif // MATERIALMANAGER_H