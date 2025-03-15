#include "core/ObjectManager.h"

// Initialise Instance
ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager()
	: objectCounter(0)
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

	object->id = objectCounter++;
	objectVector.push_back(object);
	std::cout << "Functional: Added Object to Object Map" << std::endl;
}

void ObjectManager::deleteObject(int index)
{
	objectVector.erase(objectVector.begin() + index);
	objectCounter--;
	std::cout << "Functional: Deleted Object from Object Map - ID: " << index << std::endl;
}

std::shared_ptr<Object> ObjectManager::getObject(int index)
{
	if (index > objectVector.size())
		return nullptr;

	return objectVector[index];
}

std::vector<std::shared_ptr<Object>> ObjectManager::getObjectsVector()
{
	return objectVector;
}

int ObjectManager::getObjectCount()
{
	return objectCounter;
}

void ObjectManager::renderObjects(std::shared_ptr<Shader> s, std::shared_ptr<Shader> ls)
{
	for (auto object : objectVector)
	{
		s->use();
		object->draw(s, SHADER_DEFAULT);
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