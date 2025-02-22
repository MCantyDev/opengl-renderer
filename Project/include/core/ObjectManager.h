#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "mesh/Object.h"

#include <string>
#include <iostream>
#include <unordered_map>

class ObjectManager
{
public:
	ObjectManager* GetInstance();
	void DeleteInstance();
	
	~ObjectManager();

	Object* getObjects();

	void addObject(const Object& object);
	void deleteObject(std::string objectName);

private:
	ObjectManager();
	static ObjectManager* instance;
	
	std::unordered_map<std::string, Object> objectMap;

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