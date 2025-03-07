#include "core/SceneManager.h"

SceneManager::SceneManager()
	: camera(Camera::GetInstance()), objectManager(ObjectManager::GetInstance()), materialManager(MaterialManager::GetInstance()), 
	lightManager(LightManager::GetInstance()), shaderManager(ShaderManager::GetInstance()), modelManager(ModelManager::GetInstance()),
	mainShader("default"), lightShader("lighting")
{
	std::cout << "Setup: Scene Manager created" << std::endl;
}

SceneManager::~SceneManager()
{
	materialManager->DestroyInstance();
	shaderManager->DestroyInstance();
	modelManager->DestroyInstance();
	objectManager->DestroyInstance();
	lightManager->DestroyInstance();
	camera->DestroyInstance();

	std::cout << "Closing: Scene Manager destroyed" << std::endl;
}

void SceneManager::initialiseSystems(GLFWwindow* window)
{
	std::cout << "Setup: Initialising default values" << std::endl;

	camera->initialiseCamera(window, glm::vec3(0.0f, 0.0f, 3.0f));
	shaderManager->addShader("default", std::make_shared<Shader>("shaders/default.vert", "shaders/default.frag"));
	shaderManager->addShader("lighting", std::make_shared<Shader>("shaders/lighting.vert", "shaders/lighting.frag"));
	materialManager->addMaterial("default", std::make_shared<Material>(Base(glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(0.5f)), 32.0f));
	lightManager->addLight(std::make_shared<DirectionalLight>( glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.4f), glm::vec3(0.75f), glm::vec3(0.06f)), DIRECTIONAL_LIGHT);

	std::cout << "Setup: Initialisation of default values complete" << std::endl;
}

void SceneManager::setCurrentShaderNames(std::string mainShader, std::string lightShader)
{
	this->mainShader = mainShader;
	this->lightShader = lightShader;
}

void SceneManager::setShaderMat4(glm::mat4 projection, glm::mat4 view)
{
	shaderManager->setupShaderMatrices(mainShader, projection, view);
	shaderManager->setupShaderMatrices(lightShader, projection, view);
}

void SceneManager::setShaderUniform(std::unordered_map<std::string, UniformType> map)
{
	shaderManager->setupShaderUniforms(mainShader, map);
}

void SceneManager::setShaderLighting()
{
	shaderManager->setupLighting(mainShader);
}

void SceneManager::cameraMovement(float deltaTime)
{
	camera->processKeyboardMovement(deltaTime);
}

void SceneManager::addObject(std::string name, std::string filePath, bool flippedTexture)
{
	if (modelManager->getModel(name))
	{
		objectManager->addObject(modelManager->getModel(name));
		return;
	}
	modelManager->addModel(name, filePath, flippedTexture);
	objectManager->addObject(modelManager->getModel(name));
}
void SceneManager::editObject(int ID, std::unordered_map<std::string, EditableObject> map)
{
	objectManager->editObject(ID, map);
}
void SceneManager::deleteObject(int ID)
{
	objectManager->deleteObject(ID);
}

void SceneManager::addMaterial(std::string materialName, std::shared_ptr<Material> material)
{
	materialManager->addMaterial(materialName.c_str(), material);
}
void SceneManager::deleteMaterial(std::string materialName)
{
	materialManager->deleteMaterial(materialName.c_str());
}

void SceneManager::addLight(std::shared_ptr<Light> light, LightType type)
{
	lightManager->addLight(light, type);
}
void SceneManager::editLight(int ID, LightType type, std::unordered_map<std::string, EditableLight> map)
{
	lightManager->editLight(0, type, map);
}
void SceneManager::deleteLight(int ID, LightType type)
{
	lightManager->deleteLight(ID, type);
}

void SceneManager::update(int width, int height)
{
	projection = glm::perspective(glm::radians(camera->getFov()), (float)(width / height), 0.1f, 100.0f);
	view = camera->getView();

	shaderManager->setupShaderMatrices(mainShader, projection, view);
	shaderManager->setupShaderMatrices(lightShader, projection, view);
	shaderManager->setupShaderUniforms(mainShader, { {"viewPos", camera->getPos()} });
	shaderManager->setupLighting(mainShader);
}

void SceneManager::render()
{
	objectManager->renderObjects(shaderManager->getShader(mainShader), shaderManager->getShader(lightShader));
}

