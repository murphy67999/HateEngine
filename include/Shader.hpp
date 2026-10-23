#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    void use() const;
    void setUniform(const std::string &uniformName, int value) const;
    void setUniform(const std::string &uniformName, float value) const;
    void setUniform(const std::string &uniformName, glm::vec3 value) const;
    void setUniform(const std::string &uniformName, glm::mat4 value) const;

private:
    GLuint m_shaderProgram = 0;
};