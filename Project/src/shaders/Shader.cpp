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
		std::cout << "SUCCESS: SHADER_FILE_SUCCESSFULLY_READ" << std::endl;
    } 
    catch (std::ifstream::failure e)
    {
        std::cerr << "ERROR: SHADER_FILE_NOT_SUCCESFULLY_READ" << std::endl;
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
		std::cerr << "ERROR: SHADER_COMPILATION_FAILED \nINFO: " << infoLog << std::endl;
	}
	std::cout << "SUCCESS: SHADER_COMPILATION_SUCCESS" << std::endl;

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
		std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED \nINFO: " << infoLog << std::endl;
	}
	else
	{
		std::cout << "SUCCESS: SHADER_PROGRAM_LINKED_SUCCESSFULY" << std::endl;
	}

	return programID;
}


// All overloaded set functions
// Set Bool Functions - Takes 1 to 4 values
void Shader::setBool(const std::string& name, bool v)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)v);
}
void Shader::setBool(const std::string& name, bool v1, bool v2)
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), (int)v1, (int)v2);
}
void Shader::setBool(const std::string& name, bool v1, bool v2, bool v3)
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), (int)v1, (int)v2, (int)v3);
}
void Shader::setBool(const std::string& name, bool v1, bool v2, bool v3, bool v4)
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), (int)v1, (int)v2, (int)v3, (int)v4);
}

// Set Integer Functions - Takes 1 to 4 Values
void Shader::setInt(const std::string& name, int v)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
}
void Shader::setInt(const std::string& name, int v1, int v2)
{
	glUniform2i(glGetUniformLocation(ID, name.c_str()), v1, v2);
}
void Shader::setInt(const std::string& name, int v1, int v2, int v3)
{
	glUniform3i(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}
void Shader::setInt(const std::string& name, int v1, int v2, int v3, int v4)
{
	glUniform4i(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
}

// Set Float Functions - Takes 1 to 4 values
void Shader::setFloat(const std::string& name, float v)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), v);
}
void Shader::setFloat(const std::string& name, float v1, float v2)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), v1, v2);
}
void Shader::setFloat(const std::string& name, float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}
void Shader::setFloat(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
}

// Functions which are using GLM Vectors instead of just standard floats
void Shader::setFloat(const std::string& name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}
void Shader::setFloat(const std::string& name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::setFloat(const std::string& name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}