#include "core/ObjectManager.h"

// Initialise Instance
ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager()
{
	std::cout << "Setup: Object Manager created" << std::endl;
}

ObjectManager::~ObjectManager()
{
	std::cout << "Closing: Object Manager destroyed" << std::endl;
}

ObjectManager* ObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}
	return instance;
}

void ObjectManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ObjectManager::addObject(std::shared_ptr<Object> object, ObjectType type)
{
	std::string typeName;
	if (type == BASE_OBJECT)
	{
		object->id = baseObjectCounter;
		objectMap[type][baseObjectCounter++] = object;
		typeName = "Base Object";
		
	}

	if (type == LIGHT_SOURCE)
	{
		object->id = lightSourceCounter;
		objectMap[type][lightSourceCounter++] = object;
		typeName = "Light Source";
	}

	std::cout << "Functional: Added " << typeName << " to Object Map" << std::endl;
}

void ObjectManager::deleteObject(int ID, ObjectType type)
{
	auto typeIt = objectMap.find(type);
	if (typeIt != objectMap.end())
	{
		auto& innerMap = typeIt->second;
		innerMap.erase(ID);

		if (innerMap.empty())
			objectMap.erase(type);
	}
}

std::shared_ptr<Object> ObjectManager::getObject(int ID, ObjectType type)
{
	auto typeIt = objectMap.find(type);
	if (typeIt != objectMap.end())
	{
		auto& innerMap = typeIt->second;
		
		auto objectIt = innerMap.find(ID);
		if (objectIt != innerMap.end())
		{
			return objectIt->second;
		}
	}
	return nullptr;
}

void ObjectManager::renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls)
{
	std::unordered_map<int, std::shared_ptr<Object>> renderables;
	
	renderables = objectMap[BASE_OBJECT];
	for (auto object : renderables)
	{
		s->use();
		object.second->draw(s);
	}

	renderables = objectMap[LIGHT_SOURCE];
	for (auto object : renderables)
	{
		ls->use();
		object.second->draw(ls, SHADER_LIGHTING);
	}
}