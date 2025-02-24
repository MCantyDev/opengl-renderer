#include "core/LightManager.h"

LightManager* LightManager::instance = nullptr;

LightManager::LightManager()
	: nextDirectionalID(0), nextPointID(0), nextSpotID(0), numLights(0)
{
	std::cout << "Setup: Light Manager created" << std::endl;
}

LightManager::~LightManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing Light Manager destroyed" << std::endl;
	}
}

LightManager* LightManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new LightManager();
	}
	return instance;
}

void LightManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing Light Manager destroyed" << std::endl;
	}
}

void LightManager::addLight(std::shared_ptr<Light> light, LightType lightType)
{
	if (lightType == DIRECTIONAL_LIGHT)
	{
		lightMap[lightType][nextDirectionalID] = light;
		nextDirectionalID++;
	}

	if (lightType == POINT_LIGHT)
	{
		lightMap[lightType][nextPointID] = light;
		nextPointID++;
	}
	
	if (lightType == SPOT_LIGHT)
	{
		lightMap[lightType][nextSpotID] = light;
		nextSpotID++;
	}
	numLights++;
	std::cout << "Functional: Adding " << getLightTypeName(lightType) << " to Light Manager" << std::endl;
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
			numLights--;
		}
		std::cout << "Functional: Removing " << getLightTypeName(lightType) << " from Light Manager - " << getLightTypeName(lightType) << " ID: \"" << lightID << "\"" << std::endl;
	}
}

std::shared_ptr<Light> LightManager::getLight(int lightID, LightType lightType)
{
	auto typeIt = lightMap.find(lightType);

	if (typeIt != lightMap.end())
	{
		auto innerMap = typeIt->second;
		auto it = innerMap.find(lightID);

		if (it != innerMap.end())
		{
			return it->second;
		}
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