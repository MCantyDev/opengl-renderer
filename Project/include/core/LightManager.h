#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"
#include "lighting/SpotLight.h"

#include <unordered_map>
#include <iostream>
#include <memory>
#include <variant>

using EditableLight = std::variant<
	glm::vec3, float, std::shared_ptr<Object>>;

class LightManager
{
public:
	static LightManager* GetInstance();
	static void DestroyInstance();

	~LightManager();

	void addLight(std::shared_ptr<Light> light, LightType lightType);
	void editLight(int id, LightType type, std::unordered_map<std::string, EditableLight> map);
	void deleteLight(int id, LightType lightType);

	std::shared_ptr<Light> getLight(int id, LightType type);
	std::shared_ptr<DirectionalLight> getDirectionalLight(int id);
	std::shared_ptr<PointLight> getPointLight(int id);
	std::shared_ptr<SpotLight> getSpotLight(int id);

	int getMapSize(LightType lightType);

	std::vector<std::shared_ptr<Object>> getLightMeshes();

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

	std::unordered_map<LightType, std::unordered_map<int, std::shared_ptr<Light>>> lightMap;

	std::string getLightTypeName(LightType type);
};

#endif // LIGHTMANAGER_H