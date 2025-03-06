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

void ObjectManager::addObject(std::shared_ptr<Object> object)
{

	object->id = objectCounter;
	objectMap[objectCounter++] = object;
	std::cout << "Functional: Added Object to Object Map" << std::endl;
}

void ObjectManager::deleteObject(int ID)
{
	objectMap.erase(ID);
	std::cout << "Functional: Deleted Object from Object Map - ID: " << ID << std::endl;
}

std::shared_ptr<Object> ObjectManager::getObject(int ID)
{
	auto objectIt = objectMap.find(ID);
	if (objectIt != objectMap.end())
	{
		return objectIt->second;
	}
	return nullptr;
}

void ObjectManager::renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls)
{
	std::unordered_map<int, std::shared_ptr<Object>> renderables;
	
	for (auto object : objectMap)
	{
		s->use();
		object.second->draw(s);
	}

	std::vector<std::shared_ptr<Object>> lightMeshes = lightManager->getLightMeshes();
	for (auto mesh : lightMeshes)
	{
		ls->use();
		mesh->draw(ls, SHADER_LIGHTING);
	}
}

void ObjectManager::editObject(int id, std::unordered_map<std::string, EditableObject> map)
{
	std::shared_ptr<Object> object = getObject(id);

	for (const auto& [name, value] : map)
	{
		std::visit([&](auto&& v) {
			using T = std::decay_t<decltype(v)>;

			if constexpr (std::is_same_v<T, glm::vec3>) {
				if (name == "position") object->setPosition(v);
				if (name == "scale") object->setScale(v);
			}

			if constexpr (std::is_same_v<T, Rotation>)
				object->setRotation(v.rotation, v.axis);

			if constexpr (std::is_same_v<T, std::string>)
				object->setMaterial(v);
			}, value);
	};
}