#include "core/LightManager.h"

LightManager* LightManager::instance = nullptr;

LightManager::LightManager()
	: nextDirectionalID(0), nextPointID(0), nextSpotID(0)
{
	std::cout << "Setup: Light Manager created" << std::endl;
}

LightManager::~LightManager()
{
	std::cout << "Closing Light Manager destroyed" << std::endl;
}

LightManager* LightManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new LightManager();
	}
	return instance;
}

void LightManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void LightManager::addLight(LightVariant light, LightType lightType)
{
	if (lightType == DIRECTIONAL_LIGHT)
	{
		if (lightMap[DIRECTIONAL_LIGHT].size() == directionalLimit)
		{
			std::cout << "Functional Error: Failed to add Directional Light to Light Manager - " << lightMap[DIRECTIONAL_LIGHT].size() << "/" << directionalLimit << " Spots used" << std::endl;
			return;
		}
		lightMap[lightType][nextDirectionalID] = light;
		std::cout << "Functional: Adding Directional Light to Light Manager - " << lightMap[DIRECTIONAL_LIGHT].size() << " / " << directionalLimit << " Spots used" << std::endl;
		nextDirectionalID++;
	}

	if (lightType == POINT_LIGHT)
	{
		if (lightMap[POINT_LIGHT].size() == pointLimit)
		{
			std::cout << "Functional Error: Failed to add Point Light to Light Manager - " << lightMap[POINT_LIGHT].size() << "/" << pointLimit << " Spots used" << std::endl;
			return;
		}
		lightMap[lightType][nextPointID] = light;
		std::cout << "Functional: Adding Point Light to Light Manager - " << lightMap[POINT_LIGHT].size() << " / " << pointLimit << " Spots used" << std::endl;
		nextPointID++;
	}
	
	if (lightType == SPOT_LIGHT)
	{
		if (lightMap[SPOT_LIGHT].size() == spotLimit)
		{
			std::cout << "Functional Error: Failed to add Spot Light to Light Manager - " << lightMap[SPOT_LIGHT].size() << "/" << spotLimit << " Spots used" << std::endl;
			return;
		}
		lightMap[lightType][nextSpotID] = light;
		std::cout << "Functional: Adding Spot Light to Light Manager - " << lightMap[SPOT_LIGHT].size() << " / " << spotLimit << " Spots used" << std::endl;
		nextSpotID++;
	}
}

void LightManager::deleteLight(int lightID, LightType lightType)
{
	auto typeIt = lightMap.find(lightType);

	if (typeIt != lightMap.end())
	{
		auto innerMap = typeIt->second;
		innerMap.erase(lightID);
		if (innerMap.empty())
		{
			lightMap.erase(lightType);
		}
		std::cout << "Functional: Removing " << getLightTypeName(lightType) << " from Light Manager - " << getLightTypeName(lightType) << " ID: \"" << lightID << "\"" << std::endl;
	}
}

std::shared_ptr<DirectionalLight> LightManager::getDirectionalLight(int id)
{
	auto innerMap = lightMap[DIRECTIONAL_LIGHT];

	auto it = innerMap.find(id);
	if (it != innerMap.end())
	{
		return std::get<std::shared_ptr<DirectionalLight>>(it->second);
	}
	return nullptr;
}

std::shared_ptr<PointLight> LightManager::getPointLight(int id)
{
	auto innerMap = lightMap[POINT_LIGHT];
	
	auto it = innerMap.find(id);
	if (it != innerMap.end())
	{
		return std::get<std::shared_ptr<PointLight>>(it->second);
	}
	return nullptr;
}

std::shared_ptr<SpotLight> LightManager::getSpotLight(int id)
{
	auto innerMap = lightMap[SPOT_LIGHT];

	auto it = innerMap.find(id);
	if (it != innerMap.end())
	{
		return std::get<std::shared_ptr<SpotLight>>(it->second);
	}
	return nullptr;
}

int LightManager::getMapSize(LightType lightType)
{
	auto typeIt = lightMap.find(lightType);

	if (typeIt != lightMap.end())
	{
		auto innerMap = typeIt->second;
		
		return innerMap.size();
	}
	return 0;
}

std::string LightManager::getLightTypeName(LightType type)
{
	switch (type)
	{
		case DIRECTIONAL_LIGHT: 
			return "Directional Light";
		case POINT_LIGHT: 
			return "Point Light";
		case SPOT_LIGHT:
			return "Spot LIght";
		default:
			return "Unknown";
	}
}