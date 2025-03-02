#include "core/ShaderManager.h"

// Setup the Instance
ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{
	std::cout << "Setup: Shader Manager created" << std::endl;
}

ShaderManager::~ShaderManager()
{
	std::cout << "Closing: Shader Manager destroyed" << std::endl;
}

ShaderManager* ShaderManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ShaderManager();
	}
	return instance;
}

void ShaderManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void ShaderManager::addShader(std::string name, std::shared_ptr<Shader> shader)
{
	shaderMap[name] = shader;
	std::cout << "Functional: Shader \"" << name << "\" added to Shader Manager" << std::endl;
}

void ShaderManager::deleteShader(std::string name)
{
	shaderMap.erase(name);
	std::cout << "Functional: Shader \"" << name << "\" removed from Shader Manager" << std::endl;
}

std::shared_ptr<Shader> ShaderManager::getShader(std::string name)
{
	auto shaderIt = shaderMap.find(name);
	
	if (shaderIt != shaderMap.end())
	{
		return shaderIt->second;
	}
	return nullptr;
}

void ShaderManager::setupShaderMatrices(std::string name, glm::mat4 projection, glm::mat4 view)
{
	std::shared_ptr<Shader> shader = getShader(name);

	shader->use();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
}

void ShaderManager::setupShaderUniforms(std::string name, std::unordered_map<std::string, UniformType> uniformMap)
{
	std::shared_ptr<Shader> shader = getShader(name);
	shader->use();

	for (const auto& [name, value] : uniformMap)
	{
		std::visit([&](auto&& v) {
			using T = std::decay_t<decltype(v)>;

			if constexpr (std::is_same_v<T, int>)
				shader->setInt(name, v);

			else if constexpr (std::is_same_v<T, bool>)
				shader->setBool(name, v);

			else if constexpr (std::is_same_v<T, float>)
				shader->setFloat(name, v);

			else if constexpr (std::is_same_v<T, glm::vec2>)
				shader->setVec2(name, v);

			else if constexpr (std::is_same_v<T, glm::vec3>)
				shader->setVec3(name, v);

			else if constexpr (std::is_same_v<T, glm::vec4>)
				shader->setVec4(name, v);

			else if constexpr (std::is_same_v<T, glm::mat4>)
				shader->setMat4(name, v);
		}, value);
	}
}

void ShaderManager::setupLighting(std::string name)
{
	std::shared_ptr<Shader> shader = getShader(name);
	shader->use();
	
	// Get Map Sizes
	int dirSize = lightManager->getMapSize(DIRECTIONAL_LIGHT);
	int pointSize = lightManager->getMapSize(POINT_LIGHT);
	int spotSize = lightManager->getMapSize(SPOT_LIGHT);
	
	// Setup Light Values
	std::string starter;
	
	// Directional Lights
	shader->setInt("numDirLights", dirSize);
	starter = "dirLights[";
	for (int i = 0; i < dirSize; i++)
	{
		std::shared_ptr<DirectionalLight> dirLight = lightManager->getDirectionalLight(i);
		shader->setVec3(starter + std::to_string(i) + "].direction", dirLight->direction);
		shader->setVec3(starter + std::to_string(i) + "].ambient", dirLight->ambient);
		shader->setVec3(starter + std::to_string(i) + "].diffuse", dirLight->diffuse);
		shader->setVec3(starter + std::to_string(i) + "].specular", dirLight->specular);
	}

	// Point Lights
	shader->setInt("numPointLights", pointSize);
	starter = "pointLights[";
	for (int i = 0; i < pointSize; i++)
	{
		std::shared_ptr<PointLight> pointLight = lightManager->getPointLight(i);
		shader->setVec3(starter + std::to_string(i) +"].position", pointLight->position);
		shader->setVec3(starter + std::to_string(i) + "].ambient", pointLight->ambient);
		shader->setVec3(starter + std::to_string(i) + "].diffuse", pointLight->diffuse);
		shader->setVec3(starter + std::to_string(i) + "].specular", pointLight->specular);
		shader->setFloat(starter + std::to_string(i) + "].constant", pointLight->constant);
		shader->setFloat(starter + std::to_string(i) + "].linear", pointLight->linear);
		shader->setFloat(starter + std::to_string(i) + "].quadratic", pointLight->quadratic);
	}

	// Spot Lights
	shader->setInt("numSpotLights", spotSize);
	starter = "spotLights[";
	for (int i = 0; i < spotSize; i++)
	{
		std::shared_ptr<SpotLight> spotLight = lightManager->getSpotLight(i);
		shader->setVec3(starter + std::to_string(i) + "].position", spotLight->position);
		shader->setVec3(starter + std::to_string(i) + "].direction", spotLight->direction);
		shader->setVec3(starter + std::to_string(i) + "].ambient", spotLight->ambient);
		shader->setVec3(starter + std::to_string(i) + "].diffuse", spotLight->diffuse);
		shader->setVec3(starter + std::to_string(i) + "].specular", spotLight->specular);
		shader->setFloat(starter + std::to_string(i) + "].constant", spotLight->constant);
		shader->setFloat(starter + std::to_string(i) + "].linear", spotLight->linear);
		shader->setFloat(starter + std::to_string(i) + "].quadratic", spotLight->quadratic);
		shader->setFloat(starter + std::to_string(i) + "].innerCutOff", spotLight->innerCutOff);
		shader->setFloat(starter + std::to_string(i) + "].outerCutOff", spotLight->outerCutOff);
	}
}