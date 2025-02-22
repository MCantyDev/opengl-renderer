#include "core/ObjectManager.h"

// Initialise Instance
ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager()
{
	std::cout << "Setup: Object Manager created" << std::endl;
}

ObjectManager::~ObjectManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Object Manager destroyed" << std::endl;
	}
}

ObjectManager* ObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}
	return instance;
}

void ObjectManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Object Manager destroyed" << std::endl;
	}
}