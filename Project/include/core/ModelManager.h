#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "mesh/Model.h"
#include "core/AssimpLoader.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

class ModelManager
{
public:
	static ModelManager* GetInstance();
	static void DestroyInstance();

	~ModelManager();

	void addModel(std::string name, std::string filePath, bool flipped = false);
	void deleteModel(std::string name);

	std::shared_ptr<Model> getModel(std::string name);

	size_t getModelCount();
	std::string getModelName(int index);
	std::vector<std::string> getModelNames();

private:
	ModelManager();
	static ModelManager* instance;

	AssimpLoader assimpLoader;
	std::unordered_map<std::string, std::shared_ptr<Model>> modelMap;
	std::vector<std::string> modelNames;

	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
};

#endif // MODELMANAGER_H