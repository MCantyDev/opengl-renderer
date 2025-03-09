#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "glad/glad.h"
#include "core/LightManager.h"
#include "mesh/Object.h"

// Primitive Meshes
#include "mesh/Cube.h"
#include "mesh/Sphere.h"

#include <iostream>
#include <unordered_map>
#include <memory>
#include <variant>

using EditableObject = std::variant<
	glm::vec3, Rotation, std::string>;

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
	~ObjectManager();

	void addObject(std::shared_ptr<Object> object);
	void editObject(int index, std::unordered_map<std::string, EditableObject> map);
	void deleteObject(int index);

	std::shared_ptr<Object> getObject(int ID);
	std::vector<std::shared_ptr<Object>> getObjectsVector();
	int getObjectCount();

	void renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls);
private:
	ObjectManager();
	static ObjectManager* instance;
	LightManager* lightManager = LightManager::GetInstance();

	int objectCounter;

	std::vector<std::shared_ptr<Object>> objectVector;

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