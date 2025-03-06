#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "core/LightManager.h"
#include "mesh/Object.h"
#include "glad/glad.h"


#include <iostream>
#include <unordered_map>
#include <memory>

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
	~ObjectManager();

	void addObject(std::shared_ptr<Object> object);
	void deleteObject(int ID);

	std::shared_ptr<Object> getObject(int ID);

	void renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls);

private:
	ObjectManager();
	static ObjectManager* instance;
	LightManager* lightManager = LightManager::GetInstance();

	int objectCounter;

	std::unordered_map<int, std::shared_ptr<Object>> objectMap;

	// Delete the Copy Constructor
	ObjectManager(const ObjectManager&) = delete;
	// Delete the Copy Assignment
	ObjectManager& operator=(const ObjectManager&) = delete;

	// Delete the Move Constructor
	ObjectManager(ObjectManager&&) = delete;
	// Delete the Move Assignment
	ObjectManager& operator=(ObjectManager&&) = delete;
};
#endif // OBJECTMANAGER_H