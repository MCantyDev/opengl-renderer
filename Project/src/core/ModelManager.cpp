#include "core/ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
	std::cout << "Setup: Model Manager created" << std::endl;
}

ModelManager::~ModelManager()
{
	std::cout << "Closing: Model Manager destroyed" << std::endl;
}

ModelManager* ModelManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ModelManager();
	}
	return instance;
}

void ModelManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ModelManager::addModel(std::string name, std::string filePath, bool flipped)
{
	std::shared_ptr<Model> model = std::make_shared<Model>(assimpLoader.load(filePath, flipped));
	modelMap[name] = model;
	std::cout << "Functional: Model added to Model Manager - Name: \"" << name << "\"" << std::endl;
}

void ModelManager::deleteModel(std::string name)
{
	modelMap.erase(name);
	std::cout << "Functional: Model removed from Model Manager - Name: " << name << "\"" << std::endl;
}

std::shared_ptr<Model> ModelManager::getModel(std::string name)
{
	auto modelIt = modelMap.find(name);
	
	if (modelIt != modelMap.end())
	{
		return modelIt->second->clone();
	}
	return nullptr;
}