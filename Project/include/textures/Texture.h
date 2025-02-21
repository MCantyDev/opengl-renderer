#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
    // Constructor that loads a texture
    Texture() = default;
    Texture(const std::string& filePath, bool flipped = false);
    ~Texture();

    void bind() const;
    void activateTexture(GLuint textureUnit) const;

    void setTextureParams(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter);

    GLuint getID() const;
private:
    GLuint ID = 0;
    std::string path;
};

#endif // TEXTURE_H