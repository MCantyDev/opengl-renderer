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
    Texture(const std::string& filePath);
    ~Texture();

    void bind() const;
    void activateTexture(GLuint textureUnit);

    void setTextureParams(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter);

    GLuint getID();
private:
    GLuint ID;
    std::string path;
};

#endif // TEXTURE_H