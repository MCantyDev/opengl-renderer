#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "mesh/Object.h"
#include "glad/glad.h"


#include <iostream>
#include <unordered_map>
#include <memory>

enum ObjectType
{
	BASE_OBJECT,
	LIGHT_SOURCE
};

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
	~ObjectManager();

	void addObject(std::shared_ptr<Object> object, ObjectType type);
	void deleteObject(int ID, ObjectType type);

	std::shared_ptr<Object> getObject(int ID, ObjectType type);

	void renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls);

private:
	ObjectManager();
	static ObjectManager* instance;
	
	int baseObjectCounter;
	int lightSourceCounter;

	std::unordered_map<ObjectType, std::unordered_map<int, std::shared_ptr<Object>>> objectMap;

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