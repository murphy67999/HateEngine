#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture(const std::string &texturePath, GLint internalFormat);
    ~Texture();
    void bind() const;

private:
    GLuint m_texture = 0;
};