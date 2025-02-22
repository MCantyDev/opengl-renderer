#include "core/TextureManager.h"

// For Singleton
TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
{
	std::cout << "Setup: Texture Manager created" << std::endl;
}

TextureManager::~TextureManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Texture Manager destroyed" << std::endl;
	}
}

TextureManager* TextureManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
		std::cout << "Closing: Texture Manager destroyed" << std::endl;
	}
}

GLuint TextureManager::getTexture(const char* textureName)
{
	auto it = textureMap.find(textureName);

	if (it != textureMap.end())
	{
		return it->second;
	}
	return -1;
}

void TextureManager::addTexture(const char* textureName, const char* texturePath)
{
	GLuint texture = loadTexture(texturePath);

	if (texture == -1)
	{
		std::cout << "Error: Failed to load texture: " << texturePath << std::endl;
		return;
	}
	textureMap.insert({textureName, texture});
	std::cout << "Functional: Adding Texture to Texture Manager - Name: \"" << textureName << "\"" << std::endl;
}

void TextureManager::deleteTexture(const char* textureName)
{
	textureMap.erase(textureName);
	std::cout << "Functional: Removing Texture from Texture Manager - Name: \"" << textureName << "\"" << std::endl;
}

GLuint TextureManager::loadTexture(const char* path)
{
	GLuint ID;
	glGenTextures(1, &ID);
	int width, height, nrChannels;
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