#include "stb_image.h"
#include <string>

#include "Texture.hpp"

Texture::Texture(const std::string& texturePath, GLint internalFormat){
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* ptr_data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, ptr_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(ptr_data);
}

void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
