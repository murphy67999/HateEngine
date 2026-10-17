#pragma once

#include <string>
#include <glad/glad.h>

class Shader{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
    void use() const;
    void setUniformInt(const std::string& uniformName, int value) const;

private:
    GLuint m_shaderProgram = 0;
};