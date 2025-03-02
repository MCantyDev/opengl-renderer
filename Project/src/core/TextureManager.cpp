#include "core/TextureManager.h"

// For Singleton
TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
	std::cout << "Setup: Texture Manager created" << std::endl;
}

TextureManager::~TextureManager()
{
	std::cout << "Closing: Texture Manager destroyed" << std::endl;
}

TextureManager* TextureManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::DestroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

GLuint TextureManager::getTexture(const char* textureName, TextureType textureType)
{
	auto typeIt = textureMap.find(textureType);

	if (typeIt != textureMap.end())
	{
		auto& innerMap = typeIt->second;
		
		auto innerIt = innerMap.find(textureName);
		if (innerIt != innerMap.end())
		{
			return innerIt->second;
		}
	}
	return -1;
}

GLuint TextureManager::addTexture(const char* textureName, TextureType textureType, const char* texturePath, bool flipped)
{
	GLuint texture = loadTexture(texturePath, flipped);

	if (texture == -1)
	{
		std::cout << "Functional Error: Failed to load texture: " << texturePath << std::endl;
		return -1;
	}
	textureMap[textureType][textureName] = texture;
	std::cout << "Functional: Adding " << getTextureTypeName(textureType) << " Texture to Texture Manager - Name: \"" << textureName << "\"" << std::endl;
	return texture;
}

void TextureManager::deleteTexture(const char* textureName, TextureType textureType)
{
	auto typeIt = textureMap.find(textureType);
	
	if (typeIt != textureMap.end())
	{
		auto& innerMap = typeIt->second;
		innerMap.erase(textureName);

		if (innerMap.empty())
		{
			textureMap.erase(textureType);
		}
	}
	std::cout << "Functional: Removing " << getTextureTypeName(textureType) << " Texture from Texture Manager - Name: \"" << textureName << "\"" << std::endl;
}

GLuint TextureManager::loadTexture(const char* path, bool flipped)
{
	GLuint ID;
	glGenTextures(1, &ID);
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(flipped);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format = GL_RGBA; // Make it GL_RGBA by default 
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3)
			format = GL_RGB;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return ID;
	}
	else
	{
		return -1;
	}
	stbi_image_free(data);
}

std::string TextureManager::getTextureTypeName(TextureType type) {
	switch (type) {
		case TEXTURE_DIFFUSE:
			return "Diffuse";
		case TEXTURE_SPECULAR:
			return "Specular";
		case TEXTURE_EMISSION:
			return "Emission";
		default:             
			return "Unknown";
	}
}