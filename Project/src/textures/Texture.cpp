#include "textures/Texture.h"

// Constructor that loads the texture from the file
Texture::Texture(const std::string& filePath) : path(filePath)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture parameters
    setTextureParams(GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);  // Flip texture on load
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "SUCCESS: Successfully loaded texture: " << filePath << std::endl;
    }
    else
    {
        std::cout << "ERROR: Failed to load texture: " << filePath << std::endl;
    }
    stbi_image_free(data);
}

// Destructor to clean up
Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

GLuint Texture::getID()
{
    return ID;
}

// Binds the texture
void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

// Set texture parameters (wrap and filter)
void Texture::setTextureParams(GLenum wrapS, GLenum wrapT, GLenum minFilter, GLenum magFilter)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

// Activates the texture (binding it to a texture unit)
void Texture::activateTexture(GLuint textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);  // Activate the texture unit (e.g., GL_TEXTURE0, GL_TEXTURE1, etc.)
    bind();  // Bind the texture to the selected unit
}

