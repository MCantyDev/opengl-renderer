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
	if (modelMap.find(name) == modelMap.end())
	{
		std::shared_ptr<Model> model = std::make_shared<Model>(assimpLoader.load(filePath, flipped));
		modelMap[name] = model;

		modelNames.push_back(name);
		std::cout << "Functional: Model added to Model Manager - Name: \"" << name << "\"" << std::endl;
	}
	std::cerr << "Functional Error: Model name must be unique - Name used: \"" << name << "\"" << std::endl;
}

void ModelManager::deleteModel(std::string name)
{
	modelMap.erase(name);
	
	// I need to remove the value from the Vector too -> Using std::find from <algorithm>
	auto it = std::find(modelNames.begin(), modelNames.end(), name);
	if (it != modelNames.end())
	{
		modelNames.erase(it);
	}

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

size_t ModelManager::getModelCount()
{
	return modelNames.size();
}

std::string ModelManager::getModelName(int index)
{
	if (index > modelNames.size())
	{
		std::cerr << "Functional Error: Index exceeds the Model count" << std::endl;
		return "";
	}
	return modelNames[index];
}

std::vector<std::string> ModelManager::getModelNames()
{
	std::vector<std::string> modelNames;

	for (auto& [key, val] : modelMap)
	{
		modelNames.push_back(key);
	}
	
	return modelNames;
}