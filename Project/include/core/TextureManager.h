#ifndef TextureManager_H
#define TextureManager_H

#include <unordered_map>
#include <iostream>

#include "glad/glad.h"
#include "stb/stb_image.h"

enum TextureType
{
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
	TEXTURE_EMISSION
};

// Singleton
class TextureManager
{
public:
	static TextureManager* GetInstance();
	static void DeleteInstance();

	~TextureManager();

	GLuint getTexture(const char* textureName, TextureType textureType);
	GLuint addTexture(const char* textureName, TextureType textureType, const char* texturePath, bool flipped);

	void deleteTexture(const char* textureName, TextureType textureType);

private:
	TextureManager();
	static TextureManager* instance; 

	// Map of Textures
	std::unordered_map<TextureType, std::unordered_map<std::string, GLuint>> textureMap;

	GLuint loadTexture(const char* path, bool flipped);
	std::string getTextureTypeName(TextureType type);

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
};

#endif // TextureManager_H