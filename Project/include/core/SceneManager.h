#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "core/ShaderManager.h"
#include "core/ObjectManager.h"
#include "core/MaterialManager.h"
#include "core/LightManager.h"
#include "core/ModelManager.h"
#include "core/Camera.h"

#include <unordered_map>

/* 
	@Class Scene Manager
	@brief Scene Manager is the Class in which the core systems are called from. Scene Manager is used to interface with the whole application backend
*/
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void initialiseSystems(GLFWwindow* window);
	void setCurrentShaderNames(std::string mainShader, std::string lightShader);
	void setShaderMat4(glm::mat4 projection, glm::mat4 view);
	void setShaderUniform(std::unordered_map<std::string, UniformType> map);
	void setShaderLighting();

	void cameraMovement(float deltaTime);

	void addObject(std::string name, std::string filePath = "", bool flippedTexture = false);
	void editObject(int ID, std::unordered_map<std::string, EditableObject> map);
	void deleteObject(int ID);

	void addMaterial(std::string materialName, std::shared_ptr<Material> material);
	void deleteMaterial(std::string materialName);

	void addLight(std::shared_ptr<Light> light, LightType type);
	void editLight(int ID, LightType type, std::unordered_map<std::string, EditableLight> map);
	void deleteLight(int ID, LightType type);

	void update(int width, int height);
	void render();

private:
	// Retrieve all the pointers to the core instances (singletons)
	Camera* camera;
	ObjectManager* objectManager;
	MaterialManager* materialManager;
	LightManager* lightManager;
	ShaderManager* shaderManager;
	ModelManager* modelManager;

	glm::mat4 projection;
	glm::mat4 view;

	std::string mainShader;
	std::string lightShader;
};

#endif // SCENEMANAGER_H