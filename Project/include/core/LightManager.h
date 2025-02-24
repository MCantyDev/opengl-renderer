#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"
#include "lighting/SpotLight.h"

#include <unordered_map>
#include <iostream>
#include <memory>

enum LightType
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class LightManager
{
public:
	static LightManager* GetInstance();
	static void DeleteInstance();

	~LightManager();

	void addLight(std::shared_ptr<Light> light, LightType lightType);
	void deleteLight(int lightID, LightType lightType);

	std::shared_ptr<Light> getLight(int lightID, LightType lightType);
	int getMapSize(LightType lightType);

private:
	LightManager();
	static LightManager* instance;

	// Map IDs
	int nextDirectionalID;
	int nextPointID;
	int nextSpotID;
	// Total Number of Lights
	int numLights;

	std::unordered_map<LightType, std::unordered_map<int, std::shared_ptr<Light>>> lightMap;

	std::string getLightTypeName(LightType type);
};

#endif // LIGHTMANAGER_H