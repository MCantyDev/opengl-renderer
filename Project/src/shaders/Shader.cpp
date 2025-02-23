#include "shaders/Shader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	GLuint vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	// Creating Shader Program
	ID = createProgram(vertexShader, fragmentShader);

	// Delete Shaders from Memory as they are now within the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::clear()
{
	glDeleteProgram(ID);
}

GLuint Shader::getID()
{
	return ID;
}

std::string Shader::getFileContents(const char* filename)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(filename);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
		std::cout << "Setup: Successfully read shader file: " << filename << std::endl;
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Error: Failed to read shader file: " << filename << std::endl;
	}

	return shaderCode.c_str();
}

GLuint Shader::compileShader(const char* shaderCode, GLenum shaderType)
{
	GLuint shaderID;
	int success;
	char infoLog[512];

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cerr << "Error: Failed to compile shader program\nMore Information: " << infoLog << std::endl;
	}
	std::cout << "Setup: Successfully compiled shader" << std::endl;

	return shaderID;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint programID;
	int success;
	char infoLog[512];

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "Error: Failed to link shader program\nMore Information: " << infoLog << std::endl;
	}
	else
	{
		std::cout << "Setup: Successfully linked shader program" << std::endl;
	}

	return programID;
}

GLuint Shader::getLocation(const std::string& name)
{
	GLuint location = glGetUniformLocation(ID, name.c_str());

	if (location == -1)
	{
		std::cerr << "Warning: Uniform '" << name << "' does not exist!" << std::endl;
	}

	return location;
}

// All overloaded set functions
// Set Bool Functions - Takes 1 to 4 values
void Shader::setBool(const std::string& name, bool v)
{
	glUniform1i(getLocation(name), (int)v);
}
void Shader::setBool(const std::string& name, bool v1, bool v2)
{
	glUniform2i(getLocation(name), (int)v1, (int)v2);
}
void Shader::setBool(const std::string& name, bool v1, bool v2, bool v3)
{
	glUniform3i(getLocation(name), (int)v1, (int)v2, (int)v3);
}
void Shader::setBool(const std::string& name, bool v1, bool v2, bool v3, bool v4)
{
	glUniform4i(getLocation(name), (int)v1, (int)v2, (int)v3, (int)v4);
}

// Set Integer Functions - Takes 1 to 4 Values
void Shader::setInt(const std::string& name, int v)
{
	glUniform1i(getLocation(name), v);
}
void Shader::setInt(const std::string& name, int v1, int v2)
{
	glUniform2i(getLocation(name), v1, v2);
}
void Shader::setInt(const std::string& name, int v1, int v2, int v3)
{
	glUniform3i(getLocation(name), v1, v2, v3);
}
void Shader::setInt(const std::string& name, int v1, int v2, int v3, int v4)
{
	glUniform4i(getLocation(name), v1, v2, v3, v4);
}

// Set Float Functions - Takes 1 to 4 values
void Shader::setFloat(const std::string& name, float v)
{
	glUniform1f(getLocation(name), v);
}
void Shader::setFloat(const std::string& name, float v1, float v2)
{
	glUniform2f(getLocation(name), v1, v2);
}
void Shader::setFloat(const std::string& name, float v1, float v2, float v3)
{
	glUniform3f(getLocation(name), v1, v2, v3);
}
void Shader::setFloat(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(getLocation(name), v1, v2, v3, v4);
}

// Functions which are using GLM Vectors instead of just standard floats
void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(getLocation(name), value.x, value.y);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(getLocation(name), value.x, value.y, value.z);
}
void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4f(getLocation(name), value.x, value.y, value.z, value.w);
}

// Function which are using GLM Matrices instead of vectors
void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

// Simple Function to change the Material of the Object
void Shader::setMaterial(Material* material)
{
	if (material == nullptr)
	{
		return;
	}

	if (!material->useTexture)
	{
		// If no textures was provided to use material
		setBool("useTexture", false);

		setVec3("material.base.ambient", material->base.ambient);
		setVec3("material.base.diffuse", material->base.diffuse);
		setVec3("material.base.specular", material->base.specular);

		setFloat("material.shininess", material->shininess);
	}
	else
	{
		setBool("useTexture", true);

		bind(material->diffuseTexture, 0);
		setInt("material.diffuse", 0);

		bind(material->specularTexture, 1);
		setInt("material.specular", 1);

		bind(material->emissionTexture, 2);
		setInt("material.emission", 2);

		setFloat("material.shininess", material->shininess);
	}
}

void Shader::bind(GLuint texture, GLuint textureID)
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::setLight(const Light& light)
{
//	setVec3("light.position", light.position);
	setVec3("light.ambient", light.ambient);
	setVec3("light.diffuse", light.diffuse);
	setVec3("light.specular", light.specular);
}