#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"
#include "lighting/SpotLight.h"

#include <unordered_map>
#include <iostream>
#include <memory>
#include <variant>

enum LightType
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

using LightVariant = std::variant<
	std::shared_ptr<DirectionalLight>, std::shared_ptr<PointLight>, std::shared_ptr<SpotLight>>;

class LightManager
{
public:
	static LightManager* GetInstance();
	static void DestroyInstance();

	~LightManager();

	void addLight(LightVariant light, LightType lightType);
	void deleteLight(int id, LightType lightType);

	std::shared_ptr<DirectionalLight> getDirectionalLight(int id);
	std::shared_ptr<PointLight> getPointLight(int id);
	std::shared_ptr<SpotLight> getSpotLight(int id);

	int getMapSize(LightType lightType);

private:
	LightManager();
	static LightManager* instance;

	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

	// Map IDs
	int nextDirectionalID;
	int nextPointID;
	int nextSpotID;

	// Max Lights per Type
	int directionalLimit = 5;
	int pointLimit = 20;
	int spotLimit = 20;

	std::unordered_map<LightType, std::unordered_map<int, LightVariant>> lightMap;

	std::string getLightTypeName(LightType type);
};

#endif // LIGHTMANAGER_H