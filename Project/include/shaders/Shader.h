#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "material/Material.h"
#include "lighting/Light.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum ShaderType
{
	SHADER_DEFAULT,
	SHADER_LIGHTING
};

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);

	void use();
	void clear();

	// Overloading Function
	void setBool(const std::string& name, bool v);
	void setBool(const std::string& name, bool v1, bool v2);
	void setBool(const std::string& name, bool v1, bool v2, bool v3);
	void setBool(const std::string& name, bool v1, bool v2, bool v3, bool v4);

	void setInt(const std::string& name, int v);
	void setInt(const std::string& name, int v1, int v2);
	void setInt(const std::string& name, int v1, int v2, int v3);
	void setInt(const std::string& name, int v1, int v2, int v3, int v4);

	void setFloat(const std::string& name, float v);
	void setFloat(const std::string& name, float v1, float v2);
	void setFloat(const std::string& name, float v1, float v2, float v3);
	void setFloat(const std::string& name, float v1, float v2, float v3, float v4);

 	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec4(const std::string& name, const glm::vec4& value);
	
	void setMat4(const std::string& name, const glm::mat4& mat);
	
	// Overloaded as sometimes i may not have a texture
	void setMaterial(std::shared_ptr<Material> material, ShaderType type);

	void setLight(const Light& light);
	
	GLuint getID();

private:
	GLuint ID;

	std::string getFileContents(const char* filename);
	GLuint compileShader(const char* shaderCode, GLenum shaderType);
	GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
	GLuint getLocation(const std::string& name);
	void bind(GLuint texture, GLuint textureID);
};

#endif // SHADER_H