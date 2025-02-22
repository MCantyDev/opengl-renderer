#include "core/MaterialManager.h"

// Defining Instance
MaterialManager* MaterialManager::instance = nullptr;

MaterialManager::MaterialManager()
{
	std::cout << "Setup: Material Manager created" << std::endl;
}

MaterialManager::~MaterialManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Material Manager destroyed" << std::endl;
	}
}

MaterialManager* MaterialManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MaterialManager();
	}
	return instance;
}

void MaterialManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Material Manager destroyed" << std::endl;
	}
}