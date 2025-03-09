#include "core/SceneManager.h"

SceneManager::SceneManager()
	: camera(Camera::GetInstance()), objectManager(ObjectManager::GetInstance()), materialManager(MaterialManager::GetInstance()), 
	lightManager(LightManager::GetInstance()), shaderManager(ShaderManager::GetInstance()), modelManager(ModelManager::GetInstance()),
	mainShader("default"), lightShader("lighting"), projection(glm::mat4(1.0f)), view(glm::mat4(1.0f))
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
	materialManager->addMaterial("default", std::make_shared<Material>(Base(glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f)), 128.0f));
	lightManager->addLight(std::make_shared<DirectionalLight>( glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.4f), glm::vec3(0.75f), glm::vec3(0.06f)), DIRECTIONAL_LIGHT);
	lightManager->addLight(std::make_shared<PointLight>
		(
			glm::vec3(1.2f, 1.0f, 2.0f),
			glm::vec3(0.05f, 0.01f, 0.01f),
			glm::vec3(0.3f, 0.3f, 0.3f),
			glm::vec3(0.1f, 0.1f, 0.1f),
			1.0f, 0.14f, 0.07f
		), POINT_LIGHT);

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

std::shared_ptr<Object> SceneManager::getObject(int ID)
{
	return objectManager->getObject(ID);
}
std::vector<std::shared_ptr<Object>> SceneManager::getObjects()
{
	return objectManager->getObjectsVector();
}
void SceneManager::addObject(std::string name)
{
	std::shared_ptr<Model> model = modelManager->getModel(name);
	if (model == nullptr)
	{
		std::cerr << "Functional Error: Model with name - " << name << " - Does not exist in Model Manager" << std::endl;
		return;
	}
	model->name = name + std::to_string(objectManager->getObjectCount());
	objectManager->addObject(model);
}
void SceneManager::addObject(std::shared_ptr<Object> object)
{
	object->name = "Primitive" + std::to_string(objectManager->getObjectCount());
	objectManager->addObject(object);
}
void SceneManager::editObject(int ID, std::unordered_map<std::string, EditableObject> map)
{
	objectManager->editObject(ID, map);
}
void SceneManager::deleteObject(int ID)
{
	objectManager->deleteObject(ID);
}

std::vector<std::shared_ptr<Light>> SceneManager::getLights()
{
	return lightManager->getLights();
}
void SceneManager::addLight(std::shared_ptr<Light> light, LightType type)
{
	lightManager->addLight(light, type);
}
void SceneManager::editLight(int ID, LightType type, std::unordered_map<std::string, EditableLight> map)
{
	lightManager->editLight(ID, type, map);
}
void SceneManager::deleteLight(int ID, LightType type)
{
	lightManager->deleteLight(ID, type);
}

std::vector<const char*> SceneManager::getMaterialNames()
{
	return materialManager->getMaterials();
}
void SceneManager::addMaterial(std::string materialName, std::shared_ptr<Material> material)
{
	materialManager->addMaterial(materialName.c_str(), material);
}
void SceneManager::deleteMaterial(std::string materialName)
{
	materialManager->deleteMaterial(materialName.c_str());
}

void SceneManager::addModel(std::string name, std::string filePath, bool flippedTexture)
{
	if (modelManager->getModel(name))
	{
		std::cout << "Functional: A Model with the name - " << name << " - Already exist in Model Manager" << std::endl;
		return;
	}
	modelManager->addModel(name, filePath, flippedTexture);
}
void SceneManager::deleteModel(std::string name)
{
	modelManager->deleteModel(name);
}
size_t SceneManager::getModelCount()
{
	return modelManager->getModelCount();
}
std::string SceneManager::getModelName(int index)
{
	return modelManager->getModelName(index);
}
std::vector<std::string> SceneManager::getModelNames()
{
	return modelManager->getModelNames();
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

