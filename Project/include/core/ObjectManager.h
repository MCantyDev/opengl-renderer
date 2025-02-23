#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "mesh/Object.h"

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
	void deleteObject(int ID);

private:
	ObjectManager();
	static ObjectManager* instance;
	
	std::unordered_map<int, Object> objectMap;

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