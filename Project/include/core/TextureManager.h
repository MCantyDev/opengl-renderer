#ifndef TextureManager_H
#define TextureManager_H

#include <unordered_map>
#include <iostream>

#include "glad/glad.h"
#include "stb/stb_image.h"

// Singleton
class TextureManager
{
public:
	static TextureManager* GetInstance();
	static void DeleteInstance();

	~TextureManager();

	GLuint getTexture(const char* textureName);

	void addTexture(const char* textureName, const char* texturePath);
	void deleteTexture(const char* textureName);

private:
	TextureManager();
	static TextureManager* instance; 

	// Map of Textures
	std::unordered_map<std::string, GLuint> textureMap;

	GLuint loadTexture(const char* path);

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
};

#endif // TextureManager_H