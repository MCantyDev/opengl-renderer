#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "core/LightManager.h"

#include "Shaders/Shader.h"

#include <string>
#include <unordered_map>
#include <memory>
#include <variant>
#include <iostream>

// Add more for more Variants for Example...Lights
using UniformType = std::variant<
	bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

class ShaderManager
{
public:
	static ShaderManager* GetInstance();
	static void DestroyInstance();

	~ShaderManager();

	void addShader(std::string name, std::shared_ptr<Shader> shader);
	void deleteShader(std::string name);
	std::shared_ptr<Shader> getShader(std::string name);

	void setupShaderMatrices(std::string name, glm::mat4 projection, glm::mat4 view);
	void setupShaderUniforms(std::string name, std::unordered_map<std::string, UniformType> uniformMap);
	void setupLighting(std::string name);

private:
	ShaderManager();
	static ShaderManager* instance;
	LightManager* lightManager = LightManager::GetInstance();

	std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;

	// Delete Copy and Move constructors
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
};

#endif // SHADERMANAGER_H